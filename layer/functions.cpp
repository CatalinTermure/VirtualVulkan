#include "functions.h"

#include <grpcpp/grpcpp.h>
#include <spdlog/spdlog.h>
#include <vk_mem_alloc.h>
#include <vulkan/vk_icd.h>
#include <vulkan/vk_layer.h>

#include <cassert>
#include <cstdlib>
#include <optional>
#include <vector>

#include "commons/remote_call.h"
#include "layer/context/device.h"
#include "layer/context/instance.h"
#include "layer/context/swapchain.h"

enum class SemaphoreState {
  kUnsignaled,
  kToBeSignaledLocal,
  kToBeSignaledRemote,
};

struct VkSemaphore_T {
  VkSemaphore local_handle = VK_NULL_HANDLE;
  VkSemaphore remote_handle = VK_NULL_HANDLE;
  VkSemaphore remote_timeline_semaphore = VK_NULL_HANDLE;
  std::binary_semaphore remote_to_local_semaphore{0};
  SemaphoreState state = SemaphoreState::kUnsignaled;
};

namespace vvk {
namespace {

constexpr uint64_t kVkQueueSubmitLocalSemaphoreTimeout = UINT64_MAX - 2;
constexpr uint64_t kVkQueueSubmitRemoteSemaphoreTimeout = UINT64_MAX - 3;
constexpr uint64_t kVkQueuePresentFenceTimeout = UINT64_MAX - 4;

const std::unordered_set<std::string> kAllowedExtensions = {
    VK_KHR_SURFACE_EXTENSION_NAME,
};

const std::unordered_set<std::string> kAllowedLayers = {
    "VK_LAYER_KHRONOS_validation",
};

template <typename T, VkStructureType sType>
T* FindLayerLinkInfo(const void* p_next_chain) {
  const T* layer_info = nullptr;
  while (p_next_chain) {
    layer_info = reinterpret_cast<const T*>(p_next_chain);
    p_next_chain = layer_info->pNext;
    if (layer_info->sType != sType) {
      continue;
    }
    if (layer_info->function == VK_LAYER_LINK_INFO) {
      break;
    }
  }
  return const_cast<T*>(layer_info);
}

void RemoveStructsFromChain(VkBaseOutStructure* base_struct, VkStructureType sType) {
  VkBaseOutStructure* next_struct = base_struct->pNext;
  VkBaseOutStructure* curr_struct = base_struct;
  while (next_struct) {
    spdlog::trace("next_struct->sType: {}", static_cast<int>(next_struct->sType));
    if (next_struct->sType == sType) {
      curr_struct->pNext = next_struct->pNext;
      next_struct = next_struct->pNext;
    } else {
      curr_struct = next_struct;
      next_struct = next_struct->pNext;
    }
  }
}

void AddStructToChain(VkBaseOutStructure* base_struct, VkBaseOutStructure* new_struct) {
  VkBaseOutStructure* next_struct = base_struct->pNext;
  base_struct->pNext = new_struct;
  new_struct->pNext = next_struct;
}

void* AllocateHandle() {
  void* handle = malloc(sizeof(VK_LOADER_DATA));
  set_loader_magic_value(handle);
  return handle;
}

std::optional<std::vector<VkImage>> GetLocalImagesForSwapchain(VkDevice device, VkSwapchainKHR swapchain) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  uint32_t swapchain_image_count = 0;
  std::vector<VkImage> client_swapchain_images;
  VkResult result =
      device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, &swapchain_image_count, nullptr);
  if (result != VK_SUCCESS) {
    return std::nullopt;
  }

  client_swapchain_images.resize(swapchain_image_count);
  result = device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, &swapchain_image_count,
                                                              client_swapchain_images.data());
  if (result != VK_SUCCESS) {
    return std::nullopt;
  }

  return client_swapchain_images;
}

}  // namespace

VKAPI_ATTR VkResult VKAPI_CALL CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo,
                                                  const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) {
  spdlog::trace("CreateSwapchainKHR");

  VkSwapchainCreateInfoKHR create_info = *pCreateInfo;
  create_info.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;

  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = device_info.dispatch_table().CreateSwapchainKHR(device, &create_info, pAllocator, pSwapchain);
  if (result != VK_SUCCESS) {
    return result;
  }

  std::optional<std::vector<VkImage>> client_swapchain_images = GetLocalImagesForSwapchain(device, *pSwapchain);
  if (!client_swapchain_images) {
    device_info.dispatch_table().DestroySwapchainKHR(device, *pSwapchain, pAllocator);
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  if (pCreateInfo->oldSwapchain) {
    RemoveSwapchainInfo(pCreateInfo->oldSwapchain);
  }

  SwapchainInfo& swapchain_info = SetSwapchainInfo(*pSwapchain, device, device_info.remote_allocator(),
                                                   *client_swapchain_images, pCreateInfo->imageExtent);

  // Create remote images for the swapchain
  VkImageCreateInfo image_create_info = {
      .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
      .imageType = VK_IMAGE_TYPE_2D,
      .format = pCreateInfo->imageFormat,
      .extent = {pCreateInfo->imageExtent.width, pCreateInfo->imageExtent.height, 1},
      .mipLevels = 1,
      .arrayLayers = pCreateInfo->imageArrayLayers,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .tiling = VK_IMAGE_TILING_OPTIMAL,
      .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | pCreateInfo->imageUsage,
      .sharingMode = pCreateInfo->imageSharingMode,
      .queueFamilyIndexCount = pCreateInfo->queueFamilyIndexCount,
      .pQueueFamilyIndices = pCreateInfo->pQueueFamilyIndices,
      .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
  };
  VmaAllocationCreateInfo alloc_create_info = {
      .flags = 0,
      .usage = VMA_MEMORY_USAGE_GPU_ONLY,
      .requiredFlags = 0,
      .preferredFlags = 0,
      .memoryTypeBits = 0,
      .pool = VK_NULL_HANDLE,
      .pUserData = nullptr,
      .priority = 0.0f,
  };
  for (VkImage client_image : *client_swapchain_images) {
    VkImage server_image;
    server_image = swapchain_info.CreateImageRemote(image_create_info, alloc_create_info);
    if (result != VK_SUCCESS) {
      device_info.dispatch_table().DestroySwapchainKHR(device, *pSwapchain, pAllocator);
      RemoveSwapchainInfo(*pSwapchain);
      return VK_ERROR_INITIALIZATION_FAILED;
    }
    device_info.swapchain_images.insert(server_image);
    device_info.SetRemoteHandle(client_image, server_image);
  }

  PresentationThreadAssociateSwapchain(*device_info.presentation_thread(), *pSwapchain, pCreateInfo->imageExtent);

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain,
                                               const VkAllocationCallbacks* pAllocator) {
  RemoveSwapchainInfo(swapchain);
  DeviceInfo& device_info = GetDeviceInfo(device);
  device_info.presentation_thread()->swapchains.erase(
      std::remove_if(device_info.presentation_thread()->swapchains.begin(),
                     device_info.presentation_thread()->swapchains.end(),
                     [swapchain](const SwapchainPresentationInfo& swapchain_present_info) {
                       return swapchain_present_info.swapchain == swapchain;
                     }),
      device_info.presentation_thread()->swapchains.end());
  device_info.dispatch_table().DestroySwapchainKHR(device, swapchain, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain,
                                                     uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  if (pSwapchainImages == nullptr) {
    return device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, nullptr);
  }
  VkResult result =
      device_info.dispatch_table().GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
  if (result != VK_SUCCESS) {
    return result;
  }

  for (uint32_t i = 0; i < *pSwapchainImageCount; i++) {
    pSwapchainImages[i] = device_info.GetRemoteHandle(pSwapchainImages[i]);
  }

  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout,
                                                   VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  InstanceInfo& instance_info = device_info.instance_info();
  if (semaphore != VK_NULL_HANDLE) {
    if (fence != VK_NULL_HANDLE) {
      throw std::runtime_error("Cannot use both semaphore and fence in AcquireNextImageKHR");
    }
    semaphore->state = SemaphoreState::kToBeSignaledLocal;
  }
  if (fence != VK_NULL_HANDLE) {
    device_info.SetFenceLocal(fence);
  }
  VkResult result = device_info.dispatch_table().AcquireNextImageKHR(device, swapchain, timeout,
                                                                     semaphore->local_handle, fence, pImageIndex);
  if (result != VK_SUCCESS) {
    semaphore->state = SemaphoreState::kUnsignaled;
    device_info.ResetFenceLocal(fence);
  }

  for (auto& swapchain_present_info : device_info.presentation_thread()->swapchains) {
    if (swapchain_present_info.swapchain != swapchain) continue;

    swapchain_present_info.swapchain_image_index = *pImageIndex;
  }

  return result;
}

VKAPI_ATTR VkResult VKAPI_CALL QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) {
  DeviceInfo& device_info = GetDeviceInfo(queue);
  VkFence aux_fence = device_info.fence_pool().GetFence();
  VkQueue local_queue = *device_info.present_queue();
  VkDevice local_device = GetDeviceForQueue(queue);
  PresentationThread& presentation_thread = *device_info.presentation_thread();
  InstanceInfo& instance_info = device_info.instance_info();
  const VkuDeviceDispatchTable& dispatch_table = device_info.dispatch_table();

  std::vector<VkSemaphore> local_semaphores_to_wait;
  std::vector<VkSemaphore> remote_semaphores_to_wait;
  std::vector<VkSwapchainKHR> swapchains;
  std::vector<uint32_t> image_indices;

  VkPresentInfoKHR present_info = *pPresentInfo;
  for (uint32_t i = 0; i < pPresentInfo->waitSemaphoreCount; i++) {
    VkSemaphore semaphore = pPresentInfo->pWaitSemaphores[i];
    if (semaphore->state == SemaphoreState::kToBeSignaledRemote) {
      remote_semaphores_to_wait.push_back(semaphore);
      semaphore->state = SemaphoreState::kUnsignaled;
    } else if (semaphore->state == SemaphoreState::kToBeSignaledLocal) {
      local_semaphores_to_wait.push_back(semaphore->local_handle);
      semaphore->state = SemaphoreState::kUnsignaled;
    } else {
      throw std::runtime_error("Invalid semaphore state in QueuePresentKHR");
    }
  }
  present_info.waitSemaphoreCount = local_semaphores_to_wait.size();
  present_info.pWaitSemaphores = local_semaphores_to_wait.data();

  for (uint32_t i = 0; i < pPresentInfo->swapchainCount; i++) {
    swapchains.push_back(pPresentInfo->pSwapchains[i]);
    image_indices.push_back(pPresentInfo->pImageIndices[i]);
  }
  present_info.pSwapchains = swapchains.data();
  present_info.pImageIndices = image_indices.data();

  if (remote_semaphores_to_wait.empty()) {
    throw std::runtime_error("No fences to wait for");
  }

  for (auto* semaphore : remote_semaphores_to_wait) {
    semaphore->remote_to_local_semaphore.acquire();
    // Unsignal the semaphore on the remote side
    {
      VkPipelineStageFlags wait_dst_stage_mask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
      VkSubmitInfo submit = {
          .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
          .pNext = nullptr,
          .waitSemaphoreCount = 1,
          .pWaitSemaphores = &semaphore->remote_handle,
          .pWaitDstStageMask = &wait_dst_stage_mask,
          .commandBufferCount = 0,
          .pCommandBuffers = nullptr,
          .signalSemaphoreCount = 0,
          .pSignalSemaphores = nullptr,
      };
      PackAndCallVkQueueSubmit(instance_info.command_stream(), device_info.GetRemoteHandle(queue), 1, &submit, nullptr);
    }
  }

  std::vector<grpc::ClientContext> client_contexts(present_info.swapchainCount);
  std::vector<std::unique_ptr<grpc::ClientReader<vvk::server::VvkGetFrameResponse>>> client_readers;
  client_readers.reserve(present_info.swapchainCount);
  for (uint32_t i = 0; i < present_info.swapchainCount; i++) {
    vvk::server::VvkGetFrameRequest request;
    for (auto& swapchain_present_info : presentation_thread.swapchains) {
      if (swapchain_present_info.swapchain == present_info.pSwapchains[i]) {
        request.set_session_key(swapchain_present_info.remote_session_key);
        request.set_frame_key(swapchain_present_info.remote_frame_keys[swapchain_present_info.swapchain_image_index]);
        request.set_width(swapchain_present_info.image_extent.width);
        request.set_height(swapchain_present_info.image_extent.height);
        break;
      }
    }
    client_readers.emplace_back(instance_info.stub().RequestFrame(&client_contexts[i], request));
  }

  for (uint32_t i = 0; i < present_info.swapchainCount; i++) {
    vvk::server::VvkGetFrameResponse response;
    std::string data;
    while (client_readers[i]->Read(&response)) {
      data.append(response.frame_data());
    }
    client_readers[i]->Finish();

    SwapchainInfo& swapchain_info = GetSwapchainInfo(present_info.pSwapchains[i]);
    swapchain_info.CopyMemoryToImage(present_info.pImageIndices[i], data, {}, {}, {}, aux_fence);
  }

  dispatch_table.WaitForFences(local_device, 1, &aux_fence, VK_TRUE, kVkQueuePresentFenceTimeout);
  dispatch_table.ResetFences(local_device, 1, &aux_fence);
  device_info.fence_pool().ReturnFence(aux_fence);

  dispatch_table.QueuePresentKHR(local_queue, &present_info);
  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL CreateWaylandSurfaceKHR(VkInstance instance,
                                                       const VkWaylandSurfaceCreateInfoKHR* pCreateInfo,
                                                       const VkAllocationCallbacks* pAllocator,
                                                       VkSurfaceKHR* pSurface) {
  InstanceInfo& instance_info = GetInstanceInfo(instance);
  VkResult result = instance_info.dispatch_table().CreateWaylandSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
  if (result != VK_SUCCESS) {
    return result;
  }

  instance_info.set_surface(*pSurface);

  return result;
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice,
                                                                  uint32_t queueFamilyIndex, VkSurfaceKHR surface,
                                                                  VkBool32* pSupported) {
  InstanceInfo& instance_info = GetInstanceInfo(physicalDevice);
  uint32_t queue_family_count;
  PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(instance_info.command_stream(), physicalDevice,
                                                      &queue_family_count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_family_properties(queue_family_count);
  PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(instance_info.command_stream(), physicalDevice,
                                                      &queue_family_count, queue_family_properties.data());
  if (queueFamilyIndex >= queue_family_count) {
    return VK_ERROR_UNKNOWN;
  }

  *pSupported = (queue_family_properties[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0;

  return VK_SUCCESS;
}

PFN_vkVoidFunction DefaultGetInstanceProcAddr(VkInstance instance, const char* pName) {
  return GetInstanceInfo(instance).dispatch_table().GetInstanceProcAddr(instance, pName);
}
PFN_vkVoidFunction DefaultGetDeviceProcAddr(VkDevice device, const char* pName) {
  return GetDeviceInfo(device).dispatch_table().GetDeviceProcAddr(device, pName);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) {
  spdlog::trace("CreateInstance");

  // TODO: what from the pNext chain do we need to pass to remote server?

  // find the next layer's GetInstanceProcAddr(GIPA) function
  const void* p_next_chain = pCreateInfo->pNext;
  const VkLayerInstanceCreateInfo* layer_instance_info =
      FindLayerLinkInfo<VkLayerInstanceCreateInfo, VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO>(p_next_chain);
  PFN_vkGetInstanceProcAddr nxt_gipa = layer_instance_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
  assert(nxt_gipa);

  // advance the linked list for the next layer
  {
    VkLayerInstanceCreateInfo* layer_instance_info_mut = const_cast<VkLayerInstanceCreateInfo*>(layer_instance_info);
    layer_instance_info_mut->u.pLayerInfo = layer_instance_info->u.pLayerInfo->pNext;
  }

  PFN_vkCreateInstance nxtCreateInstance =
      reinterpret_cast<PFN_vkCreateInstance>(nxt_gipa(nullptr, "vkCreateInstance"));
  if (!nxtCreateInstance) {
    spdlog::error("Failed to fetch vkCreateInstance from next layer");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  VkResult result = nxtCreateInstance(pCreateInfo, pAllocator, pInstance);

  std::string server_address = std::getenv("VVK_TARGET_SERVER");
  if (server_address.empty()) {
    spdlog::error("VVK_TARGET_SERVER environment variable not set");
    return VK_ERROR_INITIALIZATION_FAILED;
  }
  spdlog::info("Connecting to server at {}", server_address);
  InstanceInfo& instance_info =
      SetInstanceInfo(*pInstance, nxt_gipa, grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

  // call remote create instance
  {
    // remove loader instance create info from the pNext chain
    // the loader seems to insert these structs at the beginning of the pNext chain
    // so we can remove it by copying the instance create info and skipping the loader instance create info structs
    VkInstanceCreateInfo remote_create_info = *pCreateInfo;
    RemoveStructsFromChain(reinterpret_cast<VkBaseOutStructure*>(&remote_create_info),
                           VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO);
    VkApplicationInfo remote_app_info = *pCreateInfo->pApplicationInfo;
    remote_app_info.apiVersion = std::max(remote_app_info.apiVersion, VK_API_VERSION_1_2);
    remote_create_info.pApplicationInfo = &remote_app_info;

    std::vector<const char*> enabled_extensions;
    for (uint32_t i = 0; i < remote_create_info.enabledExtensionCount; i++) {
      if (kAllowedExtensions.contains(remote_create_info.ppEnabledExtensionNames[i])) {
        enabled_extensions.push_back(remote_create_info.ppEnabledExtensionNames[i]);
      }
    }
    remote_create_info.enabledExtensionCount = enabled_extensions.size();
    remote_create_info.ppEnabledExtensionNames = enabled_extensions.data();

    std::vector<const char*> enabled_layers;
    for (uint32_t i = 0; i < remote_create_info.enabledLayerCount; i++) {
      if (kAllowedLayers.contains(remote_create_info.ppEnabledLayerNames[i])) {
        enabled_layers.push_back(remote_create_info.ppEnabledLayerNames[i]);
      }
    }
    remote_create_info.enabledLayerCount = enabled_layers.size();
    remote_create_info.ppEnabledLayerNames = enabled_layers.data();

    auto& reader_writer = instance_info.command_stream();

    // We don't want to overwrite the local instance handle with the remote one
    VkInstance remote_instance = *pInstance;
    PackAndCallVkCreateInstance(reader_writer, &remote_create_info, pAllocator, &remote_instance);
    instance_info.SetRemoteHandle(*pInstance, remote_instance);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
  spdlog::trace("DestroyInstance");

  InstanceInfo& instance_info = GetInstanceInfo(instance);
  instance_info.dispatch_table().DestroyInstance(instance, pAllocator);

  auto& reader_writer = instance_info.command_stream();
  PackAndCallVkDestroyInstance(reader_writer, instance_info.GetRemoteHandle(instance), pAllocator);

  RemoveInstanceInfo(instance);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount,
                                                        VkPhysicalDevice* pPhysicalDevices) {
  spdlog::trace("EnumeratePhysicalDevices");

  InstanceInfo& instance_info = GetInstanceInfo(instance);

  VkResult result =
      instance_info.dispatch_table().EnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
  if (result != VK_SUCCESS) {
    return result;
  }

  if (pPhysicalDevices != nullptr) {
    for (uint32_t i = 0; i < *pPhysicalDeviceCount; i++) {
      AssociatePhysicalDeviceWithInstance(pPhysicalDevices[i], instance);
    }
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice,
                                                       VkPhysicalDeviceProperties* pProperties) {
  PackAndCallVkGetPhysicalDeviceProperties(GetInstanceInfo(physicalDevice).command_stream(), physicalDevice,
                                           pProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format,
                                                             VkFormatProperties* pFormatProperties) {
  PackAndCallVkGetPhysicalDeviceFormatProperties(GetInstanceInfo(physicalDevice).command_stream(), physicalDevice,
                                                 format, pFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo,
                                            const VkAllocationCallbacks* pAllocator, VkDevice* pDevice) {
  // find the next layer's GetDeviceProcAddr(GDPA) function
  const void* p_next_chain = pCreateInfo->pNext;
  const VkLayerDeviceCreateInfo* layer_device_info =
      FindLayerLinkInfo<VkLayerDeviceCreateInfo, VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO>(p_next_chain);
  PFN_vkGetDeviceProcAddr nxt_gdpa = layer_device_info->u.pLayerInfo->pfnNextGetDeviceProcAddr;
  assert(nxt_gdpa);

  // advance the linked list for the next layer
  {
    VkLayerDeviceCreateInfo* layer_device_info_mut = const_cast<VkLayerDeviceCreateInfo*>(layer_device_info);
    layer_device_info_mut->u.pLayerInfo = layer_device_info->u.pLayerInfo->pNext;
  }

  InstanceInfo& instance_info = GetInstanceInfo(physicalDevice);

  VkResult result;
  std::optional<uint32_t> present_queue_family_index = std::nullopt;
  {
    float queue_priorities[1] = {1.0f};
    VkDeviceCreateInfo local_create_info = *pCreateInfo;
    VkDeviceQueueCreateInfo queue_create_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        // Even if we don't need any queue, we must still create a queue on the device as per
        // VUID-VkDeviceCreateInfo-queueCreateInfoCount-arraylength
        .queueFamilyIndex = 0,
        .queueCount = 1,
        .pQueuePriorities = queue_priorities,
    };
    local_create_info.queueCreateInfoCount = 1;
    local_create_info.pQueueCreateInfos = &queue_create_info;

    auto surface = instance_info.surface();
    if (surface.has_value()) {
      uint32_t queue_family_count = 0;
      std::vector<VkQueueFamilyProperties> queue_family_properties;
      instance_info.dispatch_table().GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queue_family_count,
                                                                            nullptr);
      queue_family_properties.resize(queue_family_count);
      instance_info.dispatch_table().GetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queue_family_count,
                                                                            queue_family_properties.data());
      for (uint32_t i = 0; i < queue_family_count; i++) {
        VkBool32 supports_present = VK_FALSE;
        instance_info.dispatch_table().GetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, *surface,
                                                                          &supports_present);
        if (supports_present) {
          queue_create_info.queueFamilyIndex = i;
          present_queue_family_index = i;
          break;
        }
      }
    }

    result = instance_info.dispatch_table().CreateDevice(physicalDevice, &local_create_info, pAllocator, pDevice);
  }

  if (result != VK_SUCCESS) {
    return result;
  }

  VmaVulkanFunctions vma_vulkan_funcs = {
      .vkGetInstanceProcAddr = nullptr,
      .vkGetDeviceProcAddr = nullptr,
      .vkGetPhysicalDeviceProperties = GetPhysicalDeviceProperties,
      .vkGetPhysicalDeviceMemoryProperties = GetPhysicalDeviceMemoryProperties,
      .vkAllocateMemory = AllocateMemory,
      .vkFreeMemory = FreeMemory,
      .vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(0xDEADBEEF),
      .vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(0xDEADBEEF),
      .vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(0xDEADBEEF),
      .vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(0xDEADBEEF),
      .vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(0xDEADBEEF),
      .vkBindImageMemory = BindImageMemory,
      .vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(0xDEADBEEF),
      .vkGetImageMemoryRequirements = GetImageMemoryRequirements,
      .vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(0xDEADBEEF),
      .vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(0xDEADBEEF),
      .vkCreateImage = CreateImage,
      .vkDestroyImage = DestroyImage,
      .vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(0xDEADBEEF),
      .vkGetBufferMemoryRequirements2KHR = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2KHR>(0xDEADBEEF),
      .vkGetImageMemoryRequirements2KHR = GetImageMemoryRequirements2,
      .vkBindBufferMemory2KHR = reinterpret_cast<PFN_vkBindBufferMemory2KHR>(0xDEADBEEF),
      .vkBindImageMemory2KHR = BindImageMemory2,
      .vkGetPhysicalDeviceMemoryProperties2KHR =
          reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2KHR>(0xDEADBEEF),
      .vkGetDeviceBufferMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceBufferMemoryRequirements>(0xDEADBEEF),
      .vkGetDeviceImageMemoryRequirements = reinterpret_cast<PFN_vkGetDeviceImageMemoryRequirements>(0xDEADBEEF),
  };

  VmaAllocatorCreateInfo allocator_create_info = {
      .flags = 0,
      .physicalDevice = physicalDevice,
      .device = *pDevice,
      .preferredLargeHeapBlockSize = 0,
      .pAllocationCallbacks = nullptr,
      .pDeviceMemoryCallbacks = nullptr,
      .pHeapSizeLimit = nullptr,
      .pVulkanFunctions = &vma_vulkan_funcs,
      .instance = GetInstanceForPhysicalDevice(physicalDevice),
      // We are using Vulkan 1.0 for VMA, because the application may only use Vulkan 1.0
      .vulkanApiVersion = VK_API_VERSION_1_0,
      .pTypeExternalMemoryHandleTypes = nullptr,
  };

  auto remote_graphics_queue_family_index = [&]() -> std::optional<uint32_t> {
    uint32_t queue_family_count;
    PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(instance_info.command_stream(), physicalDevice,
                                                        &queue_family_count, nullptr);
    std::vector<VkQueueFamilyProperties> queue_family_properties(queue_family_count);
    PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(instance_info.command_stream(), physicalDevice,
                                                        &queue_family_count, queue_family_properties.data());
    for (uint32_t i = 0; i < pCreateInfo->queueCreateInfoCount; i++) {
      const VkDeviceQueueCreateInfo& queue_create_info = pCreateInfo->pQueueCreateInfos[i];
      if (queue_family_properties[queue_create_info.queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
        return queue_create_info.queueFamilyIndex;
      }
    }
    return std::nullopt;
  }();

  if (!remote_graphics_queue_family_index.has_value()) {
    spdlog::error("No graphics queue family found");
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  DeviceInfo& device_info = SetDeviceInfo(*pDevice, nxt_gdpa, physicalDevice, allocator_create_info,
                                          present_queue_family_index, *remote_graphics_queue_family_index);

  for (uint32_t i = 0; i < pCreateInfo->queueCreateInfoCount; i++) {
    const VkDeviceQueueCreateInfo& queue_create_info = pCreateInfo->pQueueCreateInfos[i];
    device_info.CreateFakeQueueFamily(queue_create_info.queueFamilyIndex, queue_create_info.queueCount);
  }

  if (device_info.present_queue().has_value()) {
    AssociateQueueWithDevice(device_info.present_queue().value(), *pDevice);
  }

  {
    VkDeviceCreateInfo remote_create_info = *pCreateInfo;
    RemoveStructsFromChain(reinterpret_cast<VkBaseOutStructure*>(&remote_create_info),
                           VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO);
    VkDevice remote_device = *pDevice;
    // TODO: check if pNext chain contains VkPhysicalDevice12Features
    VkPhysicalDeviceTimelineSemaphoreFeatures timeline_semaphore_features = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES,
        .pNext = nullptr,
        .timelineSemaphore = VK_TRUE,
    };

    AddStructToChain(reinterpret_cast<VkBaseOutStructure*>(&remote_create_info),
                     reinterpret_cast<VkBaseOutStructure*>(&timeline_semaphore_features));

    PackAndCallVkCreateDevice(instance_info.command_stream(), physicalDevice, &remote_create_info, pAllocator,
                              &remote_device);
    instance_info.SetRemoteHandle(*pDevice, remote_device);
  }

  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  device_info.dispatch_table().DestroyDevice(device, pAllocator);

  auto& reader_writer = device_info.instance_info().command_stream();
  PackAndCallVkDestroyDevice(reader_writer, device_info.instance_info().GetRemoteHandle(device), pAllocator);

  RemoveDeviceInfo(device);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount,
                                                                    VkExtensionProperties* pProperties) {
  if (!pLayerName || strcmp(pLayerName, "VK_LAYER_VVK_virtual_vulkan") != 0) {
    return VK_ERROR_LAYER_NOT_PRESENT;
  }

  // TODO: implement this
  assert(false);

  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
                                                                  const char* pLayerName, uint32_t* pPropertyCount,
                                                                  VkExtensionProperties* pProperties) {
  if (!pLayerName || strcmp(pLayerName, "VK_LAYER_VVK_virtual_vulkan") != 0) {
    InstanceInfo& instance_info = GetInstanceInfo(physicalDevice);
    return instance_info.dispatch_table().EnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount,
                                                                             pProperties);
  }

  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();

  return PackAndCallVkEnumerateDeviceExtensionProperties(command_stream, physicalDevice, pLayerName, pPropertyCount,
                                                         pProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice,
                                                             VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
  // TODO: investigate additional steps needed for this function
  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();
  PackAndCallVkGetPhysicalDeviceMemoryProperties(command_stream, physicalDevice, pMemoryProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice,
                                                     VkPhysicalDeviceFeatures* pFeatures) {
  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();
  PackAndCallVkGetPhysicalDeviceFeatures(command_stream, physicalDevice, pFeatures);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice,
                                                                  uint32_t* pQueueFamilyPropertyCount,
                                                                  VkQueueFamilyProperties* pQueueFamilyProperties) {
  auto& command_stream = GetInstanceInfo(physicalDevice).command_stream();
  PackAndCallVkGetPhysicalDeviceQueueFamilyProperties(command_stream, physicalDevice, pQueueFamilyPropertyCount,
                                                      pQueueFamilyProperties);
}

VKAPI_ATTR void VKAPI_CALL GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex,
                                          VkQueue* pQueue) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  *pQueue = device_info.GetFakeQueue(queueFamilyIndex, queueIndex);

  VkQueue remote_queue = VK_NULL_HANDLE;
  PackAndCallVkGetDeviceQueue(device_info.instance_info().command_stream(),
                              device_info.instance_info().GetRemoteHandle(device), queueFamilyIndex, queueIndex,
                              &remote_queue);
  device_info.SetRemoteHandle(*pQueue, remote_queue);
  AssociateQueueWithDevice(*pQueue, device);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo,
                                           const VkAllocationCallbacks* pAllocator, VkFence* pFence) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = device_info.dispatch_table().CreateFence(device, pCreateInfo, pAllocator, pFence);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkFenceCreateInfo fence_create_info_copy = *pCreateInfo;
  if (pCreateInfo->flags & VK_FENCE_CREATE_SIGNALED_BIT) {
    device_info.SetFenceLocal(*pFence);
    fence_create_info_copy.flags &= ~VK_FENCE_CREATE_SIGNALED_BIT;
  }
  VkFence remote_fence = VK_NULL_HANDLE;
  result = PackAndCallVkCreateFence(device_info.instance_info().command_stream(),
                                    device_info.instance_info().GetRemoteHandle(device), &fence_create_info_copy,
                                    pAllocator, &remote_fence);
  if (result != VK_SUCCESS) {
    device_info.dispatch_table().DestroyFence(device, *pFence, pAllocator);
    return result;
  }
  device_info.SetRemoteHandle(*pFence, remote_fence);
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  device_info.dispatch_table().DestroyFence(device, fence, pAllocator);
  PackAndCallVkDestroyFence(device_info.instance_info().command_stream(),
                            device_info.instance_info().GetRemoteHandle(device), device_info.GetRemoteHandle(fence),
                            pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo,
                                               const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) {
  *pSemaphore = new VkSemaphore_T;
  DeviceInfo& device_info = GetDeviceInfo(device);
  InstanceInfo& instance_info = device_info.instance_info();
  VkResult result =
      device_info.dispatch_table().CreateSemaphore(device, pCreateInfo, pAllocator, &(*pSemaphore)->local_handle);
  if (result != VK_SUCCESS) {
    return result;
  }
  VkFenceCreateInfo fence_create_info = {
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
  };
  VkSemaphore remote_semaphore = VK_NULL_HANDLE;
  result = PackAndCallVkCreateSemaphore(device_info.instance_info().command_stream(),
                                        device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                        &remote_semaphore);
  if (result != VK_SUCCESS) {
    device_info.dispatch_table().DestroySemaphore(device, (*pSemaphore)->local_handle, pAllocator);
    return result;
  }
  VkSemaphore remote_timeline_semaphore = VK_NULL_HANDLE;
  {
    VkSemaphoreTypeCreateInfo timeline_semaphore_type_create_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .pNext = nullptr,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initialValue = 0,
    };
    VkSemaphoreCreateInfo timeline_semaphore_create_info = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = &timeline_semaphore_type_create_info,
        .flags = 0,
    };

    result = PackAndCallVkCreateSemaphore(device_info.instance_info().command_stream(),
                                          device_info.instance_info().GetRemoteHandle(device),
                                          &timeline_semaphore_create_info, pAllocator, &remote_timeline_semaphore);
    if (result != VK_SUCCESS) {
      device_info.dispatch_table().DestroySemaphore(device, (*pSemaphore)->local_handle, pAllocator);
      PackAndCallVkDestroySemaphore(instance_info.command_stream(), instance_info.GetRemoteHandle(device),
                                    remote_semaphore, pAllocator);
      return result;
    }
  }
  (*pSemaphore)->remote_handle = remote_semaphore;
  (*pSemaphore)->remote_timeline_semaphore = remote_timeline_semaphore;
  (*pSemaphore)->state = SemaphoreState::kUnsignaled;
  return result;
}

VKAPI_ATTR void VKAPI_CALL DestroySemaphore(VkDevice device, VkSemaphore semaphore,
                                            const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  InstanceInfo& instance_info = device_info.instance_info();
  device_info.dispatch_table().DestroySemaphore(device, semaphore->local_handle, pAllocator);
  PackAndCallVkDestroySemaphore(instance_info.command_stream(), instance_info.GetRemoteHandle(device),
                                semaphore->remote_handle, pAllocator);
  PackAndCallVkDestroySemaphore(instance_info.command_stream(), instance_info.GetRemoteHandle(device),
                                semaphore->remote_timeline_semaphore, pAllocator);
  delete semaphore;
}

VKAPI_ATTR VkResult VKAPI_CALL AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo,
                                              const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkAllocateMemory(device_info.instance_info().command_stream(),
                                     device_info.instance_info().GetRemoteHandle(device), pAllocateInfo, pAllocator,
                                     pMemory);
}

VKAPI_ATTR void VKAPI_CALL FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkFreeMemory(device_info.instance_info().command_stream(),
                          device_info.instance_info().GetRemoteHandle(device), memory, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo,
                                           const VkAllocationCallbacks* pAllocator, VkImage* pImage) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateImage(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator, pImage);
}

VKAPI_ATTR void VKAPI_CALL DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyImage(device_info.instance_info().command_stream(),
                            device_info.instance_info().GetRemoteHandle(device), image, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory,
                                               VkDeviceSize memoryOffset) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkBindImageMemory(device_info.instance_info().command_stream(),
                                      device_info.instance_info().GetRemoteHandle(device), image, memory, memoryOffset);
}

VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory2(VkDevice device, uint32_t bindInfoCount,
                                                const VkBindImageMemoryInfo* pBindInfos) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkBindImageMemory2(device_info.instance_info().command_stream(),
                                       device_info.instance_info().GetRemoteHandle(device), bindInfoCount, pBindInfos);
}

VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements(VkDevice device, VkImage image,
                                                      VkMemoryRequirements* pMemoryRequirements) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetImageMemoryRequirements(device_info.instance_info().command_stream(),
                                          device_info.instance_info().GetRemoteHandle(device), image,
                                          pMemoryRequirements);
}

VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo,
                                                       VkMemoryRequirements2* pMemoryRequirements) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetImageMemoryRequirements2(device_info.instance_info().command_stream(),
                                           device_info.instance_info().GetRemoteHandle(device), pInfo,
                                           pMemoryRequirements);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo,
                                               const VkAllocationCallbacks* pAllocator, VkImageView* pView) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result =
      PackAndCallVkCreateImageView(device_info.instance_info().command_stream(),
                                   device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator, pView);
  if (result != VK_SUCCESS) return result;

  if (device_info.swapchain_images.contains(pCreateInfo->image)) {
    device_info.swapchain_image_views.insert(*pView);
  }

  return result;
}
VKAPI_ATTR void VKAPI_CALL DestroyImageView(VkDevice device, VkImageView imageView,
                                            const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyImageView(device_info.instance_info().command_stream(),
                                device_info.instance_info().GetRemoteHandle(device), imageView, pAllocator);
  device_info.swapchain_image_views.erase(imageView);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateCommandPool(device_info.instance_info().command_stream(),
                                        device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                        pCommandPool);
}
VKAPI_ATTR void VKAPI_CALL DestroyCommandPool(VkDevice device, VkCommandPool commandPool,
                                              const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  for (VkCommandBuffer command_buffer : GetCommandBuffersForPool(commandPool)) {
    RemoveCommandBuffer(command_buffer);
  }
  PackAndCallVkDestroyCommandPool(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), commandPool, pAllocator);
}
VKAPI_ATTR VkResult VKAPI_CALL AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo,
                                                      VkCommandBuffer* pCommandBuffers) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = PackAndCallVkAllocateCommandBuffers(device_info.instance_info().command_stream(),
                                                        device_info.instance_info().GetRemoteHandle(device),
                                                        pAllocateInfo, pCommandBuffers);
  if (result != VK_SUCCESS) {
    return result;
  }

  // Command buffers are dispatchable handles so we must allow the loader to insert the dispatch table
  // For more details, see:
  // https://github.com/KhronosGroup/Vulkan-Loader/blob/main/docs/LoaderDriverInterface.md#driver-dispatchable-object-creation

  for (uint32_t i = 0; i < pAllocateInfo->commandBufferCount; i++) {
    VkCommandBuffer remote_command_buffer = pCommandBuffers[i];
    pCommandBuffers[i] = reinterpret_cast<VkCommandBuffer>(AllocateHandle());
    device_info.SetRemoteHandle(pCommandBuffers[i], remote_command_buffer);
    AssociateCommandBufferWithDevice(pCommandBuffers[i], device);
    AssociateCommandBufferWithPool(pCommandBuffers[i], pAllocateInfo->commandPool);
  }

  return result;
}
VKAPI_ATTR void VKAPI_CALL FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount,
                                              const VkCommandBuffer* pCommandBuffers) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  for (uint32_t i = 0; i < commandBufferCount; i++) {
    free(const_cast<VkCommandBuffer>(pCommandBuffers[i]));
  }
  std::vector<VkCommandBuffer> remote_command_buffers;
  remote_command_buffers.reserve(commandBufferCount);
  for (uint32_t i = 0; i < commandBufferCount; i++) {
    RemoveCommandBuffer(pCommandBuffers[i]);
    device_info.swapchain_render_command_buffers.erase(pCommandBuffers[i]);
    remote_command_buffers.push_back(device_info.GetRemoteHandle(pCommandBuffers[i]));
  }
  PackAndCallVkFreeCommandBuffers(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), commandPool, commandBufferCount,
                                  remote_command_buffers.data());
}

VKAPI_ATTR VkResult VKAPI_CALL BeginCommandBuffer(VkCommandBuffer commandBuffer,
                                                  const VkCommandBufferBeginInfo* pBeginInfo) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  return PackAndCallVkBeginCommandBuffer(device_info.instance_info().command_stream(),
                                         device_info.GetRemoteHandle(commandBuffer), pBeginInfo);
}
VKAPI_ATTR VkResult VKAPI_CALL EndCommandBuffer(VkCommandBuffer commandBuffer) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);

  if (device_info.swapchain_render_command_buffers.contains(commandBuffer)) {
    PresentationThreadSetupFrame(*device_info.presentation_thread(), device_info.GetRemoteHandle(commandBuffer));
    device_info.swapchain_render_command_buffers.erase(commandBuffer);
  }

  return PackAndCallVkEndCommandBuffer(device_info.instance_info().command_stream(),
                                       device_info.GetRemoteHandle(commandBuffer));
}

VKAPI_ATTR void VKAPI_CALL GetImageSubresourceLayout(VkDevice device, VkImage image,
                                                     const VkImageSubresource* pSubresource,
                                                     VkSubresourceLayout* pLayout) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkGetImageSubresourceLayout(device_info.instance_info().command_stream(),
                                         device_info.instance_info().GetRemoteHandle(device), image, pSubresource,
                                         pLayout);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo,
                                                const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateRenderPass(device_info.instance_info().command_stream(),
                                       device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                       pRenderPass);
}
VKAPI_ATTR void VKAPI_CALL DestroyRenderPass(VkDevice device, VkRenderPass renderPass,
                                             const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyRenderPass(device_info.instance_info().command_stream(),
                                 device_info.instance_info().GetRemoteHandle(device), renderPass, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo,
                                                    const VkAllocationCallbacks* pAllocator,
                                                    VkPipelineLayout* pPipelineLayout) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreatePipelineLayout(device_info.instance_info().command_stream(),
                                           device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                           pPipelineLayout);
}
VKAPI_ATTR void VKAPI_CALL DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout,
                                                 const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyPipelineLayout(device_info.instance_info().command_stream(),
                                     device_info.instance_info().GetRemoteHandle(device), pipelineLayout, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo,
                                                  const VkAllocationCallbacks* pAllocator,
                                                  VkShaderModule* pShaderModule) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateShaderModule(device_info.instance_info().command_stream(),
                                         device_info.instance_info().GetRemoteHandle(device), pCreateInfo, pAllocator,
                                         pShaderModule);
}
VKAPI_ATTR void VKAPI_CALL DestroyShaderModule(VkDevice device, VkShaderModule shaderModule,
                                               const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyShaderModule(device_info.instance_info().command_stream(),
                                   device_info.instance_info().GetRemoteHandle(device), shaderModule, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache,
                                                       uint32_t createInfoCount,
                                                       const VkGraphicsPipelineCreateInfo* pCreateInfos,
                                                       const VkAllocationCallbacks* pAllocator,
                                                       VkPipeline* pPipelines) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  return PackAndCallVkCreateGraphicsPipelines(device_info.instance_info().command_stream(),
                                              device_info.instance_info().GetRemoteHandle(device), pipelineCache,
                                              createInfoCount, pCreateInfos, pAllocator, pPipelines);
}
VKAPI_ATTR void VKAPI_CALL DestroyPipeline(VkDevice device, VkPipeline pipeline,
                                           const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyPipeline(device_info.instance_info().command_stream(),
                               device_info.instance_info().GetRemoteHandle(device), pipeline, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkResult result = PackAndCallVkCreateFramebuffer(device_info.instance_info().command_stream(),
                                                   device_info.instance_info().GetRemoteHandle(device), pCreateInfo,
                                                   pAllocator, pFramebuffer);
  if (result != VK_SUCCESS) return result;

  for (uint32_t i = 0; i < pCreateInfo->attachmentCount; i++) {
    if (device_info.swapchain_image_views.contains(pCreateInfo->pAttachments[i])) {
      device_info.swapchain_framebuffers.insert(*pFramebuffer);
      break;
    }
  }

  return result;
}
VKAPI_ATTR void VKAPI_CALL DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer,
                                              const VkAllocationCallbacks* pAllocator) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  PackAndCallVkDestroyFramebuffer(device_info.instance_info().command_stream(),
                                  device_info.instance_info().GetRemoteHandle(device), framebuffer, pAllocator);
  device_info.swapchain_framebuffers.erase(framebuffer);
}

VKAPI_ATTR VkResult VKAPI_CALL WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences,
                                             VkBool32 waitAll, uint64_t timeout) {
  if (!waitAll) {
    throw std::runtime_error("WaitForFences with waitAll=false is not supported");
  }
  DeviceInfo& device_info = GetDeviceInfo(device);

  std::vector<VkFence> local_fences;
  local_fences.reserve(fenceCount);
  std::vector<VkFence> remote_fences;
  remote_fences.reserve(fenceCount);

  for (uint32_t i = 0; i < fenceCount; i++) {
    if (device_info.IsLocalFence(pFences[i])) {
      local_fences.push_back(pFences[i]);
    } else {
      remote_fences.push_back(device_info.GetRemoteHandle(pFences[i]));
    }
  }

  VkResult local_result = VK_SUCCESS;
  VkResult remote_result = VK_SUCCESS;
  std::thread local_wait_thread;
  std::thread remote_wait_thread;

  if (!local_fences.empty()) {
    local_wait_thread = std::thread([&device_info, &local_fences, &local_result, device, waitAll, timeout]() {
      local_result = device_info.dispatch_table().WaitForFences(device, local_fences.size(), local_fences.data(),
                                                                waitAll, timeout);
    });
  }
  if (!remote_fences.empty()) {
    remote_wait_thread = std::thread([&device_info, &remote_fences, &remote_result, device, waitAll, timeout]() {
      remote_result = PackAndCallVkWaitForFences(device_info.instance_info().command_stream(),
                                                 device_info.instance_info().GetRemoteHandle(device),
                                                 remote_fences.size(), remote_fences.data(), waitAll, timeout);
    });
  }

  if (local_wait_thread.joinable()) {
    local_wait_thread.join();
  }
  if (remote_wait_thread.joinable()) {
    remote_wait_thread.join();
  }

  if (local_result != VK_SUCCESS) {
    return local_result;
  }
  return remote_result;
}

VKAPI_ATTR VkResult VKAPI_CALL ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) {
  DeviceInfo& device_info = GetDeviceInfo(device);

  std::vector<VkFence> local_fences;
  local_fences.reserve(fenceCount);
  std::vector<VkFence> remote_fences;
  remote_fences.reserve(fenceCount);

  for (uint32_t i = 0; i < fenceCount; i++) {
    if (device_info.IsLocalFence(pFences[i])) {
      local_fences.push_back(pFences[i]);
    } else {
      remote_fences.push_back(device_info.GetRemoteHandle(pFences[i]));
    }
  }

  if (!local_fences.empty()) {
    VkResult result = device_info.dispatch_table().ResetFences(device, local_fences.size(), local_fences.data());
    if (result != VK_SUCCESS) {
      return result;
    }
    for (VkFence fence : local_fences) {
      device_info.ResetFenceLocal(fence);
    }
  }

  if (!remote_fences.empty()) {
    VkResult result = PackAndCallVkResetFences(device_info.instance_info().command_stream(),
                                               device_info.instance_info().GetRemoteHandle(device),
                                               remote_fences.size(), remote_fences.data());
    if (result != VK_SUCCESS) {
      return result;
    }
  }

  return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL ResetCommandPool(VkDevice device, VkCommandPool commandPool,
                                                VkCommandPoolResetFlags flags) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  for (VkCommandBuffer command_buffer : GetCommandBuffersForPool(commandPool)) {
    device_info.swapchain_render_command_buffers.erase(command_buffer);
  }
  return PackAndCallVkResetCommandPool(device_info.instance_info().command_stream(),
                                       device_info.instance_info().GetRemoteHandle(device), commandPool, flags);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginRenderPass(VkCommandBuffer commandBuffer,
                                              const VkRenderPassBeginInfo* pRenderPassBegin,
                                              VkSubpassContents contents) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdBeginRenderPass(device_info.instance_info().command_stream(),
                                  device_info.GetRemoteHandle(commandBuffer), pRenderPassBegin, contents);
  if (device_info.swapchain_framebuffers.contains(pRenderPassBegin->framebuffer)) {
    device_info.swapchain_render_command_buffers.insert(commandBuffer);
  }
}
VKAPI_ATTR void VKAPI_CALL CmdEndRenderPass(VkCommandBuffer commandBuffer) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdEndRenderPass(device_info.instance_info().command_stream(),
                                device_info.GetRemoteHandle(commandBuffer));
}

VKAPI_ATTR void VKAPI_CALL CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint,
                                           VkPipeline pipeline) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdBindPipeline(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                               pipelineBindPoint, pipeline);
}

VKAPI_ATTR void VKAPI_CALL CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount,
                                          const VkViewport* pViewports) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdSetViewport(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                              firstViewport, viewportCount, pViewports);
}
VKAPI_ATTR void VKAPI_CALL CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount,
                                         const VkRect2D* pScissors) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdSetScissor(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                             firstScissor, scissorCount, pScissors);
}

VKAPI_ATTR void VKAPI_CALL CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount,
                                   uint32_t firstVertex, uint32_t firstInstance) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdDraw(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(commandBuffer),
                       vertexCount, instanceCount, firstVertex, firstInstance);
}

VKAPI_ATTR VkResult VKAPI_CALL QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits,
                                           VkFence fence) {
  VkDevice device = GetDeviceForQueue(queue);
  DeviceInfo& device_info = GetDeviceInfo(device);

  if (fence == VK_NULL_HANDLE) {
    throw std::runtime_error("QueueSubmit with fence == VK_NULL_HANDLE is not supported");
  }
  device_info.SetFenceLocal(fence);

  std::vector<VkSemaphore> semaphores_to_wait_local;
  semaphores_to_wait_local.reserve(submitCount);  // not the exact size but it's a good guess
  std::vector<std::binary_semaphore*> local_semaphores_to_signal_from_remote;
  local_semaphores_to_signal_from_remote.reserve(submitCount);  // not the exact size but it's a good guess
  std::vector<VkSubmitInfo> submit_infos;
  submit_infos.reserve(submitCount);
  std::vector<std::vector<VkSemaphore>> semaphores_to_wait_remote;
  semaphores_to_wait_remote.resize(submitCount);
  std::vector<std::vector<VkSemaphore>> semaphores_to_signal_remote;
  semaphores_to_signal_remote.resize(submitCount);
  std::vector<std::vector<VkCommandBuffer>> command_buffers_remote;
  command_buffers_remote.resize(submitCount);

  // We look for local semaphores and remove them from the list
  // then we send the queue submit command to the server only once the semaphores are signaled
  // we check for the semaphores to be signaled using the presentation_fence of the semaphore
  // TODO: use timeline semaphores
  for (uint32_t submit_info_indx = 0; submit_info_indx < submitCount; submit_info_indx++) {
    VkSubmitInfo submit_info = pSubmits[submit_info_indx];

    for (uint32_t j = 0; j < submit_info.waitSemaphoreCount; j++) {
      if (submit_info.pWaitSemaphores[j]->state == SemaphoreState::kToBeSignaledLocal) {
        semaphores_to_wait_local.push_back(submit_info.pWaitSemaphores[j]);
      } else {
        semaphores_to_wait_remote[submit_info_indx].push_back(submit_info.pWaitSemaphores[j]->remote_handle);
      }
    }
    submit_info.waitSemaphoreCount = semaphores_to_wait_remote[submit_info_indx].size();
    submit_info.pWaitSemaphores = semaphores_to_wait_remote[submit_info_indx].data();

    for (uint32_t j = 0; j < submit_info.signalSemaphoreCount; j++) {
      semaphores_to_signal_remote[submit_info_indx].push_back(submit_info.pSignalSemaphores[j]->remote_handle);
      submit_info.pSignalSemaphores[j]->state = SemaphoreState::kToBeSignaledRemote;
      local_semaphores_to_signal_from_remote.push_back(&submit_info.pSignalSemaphores[j]->remote_to_local_semaphore);
    }
    submit_info.signalSemaphoreCount = semaphores_to_signal_remote[submit_info_indx].size();
    submit_info.pSignalSemaphores = semaphores_to_signal_remote[submit_info_indx].data();

    for (uint32_t j = 0; j < submit_info.commandBufferCount; j++) {
      command_buffers_remote[submit_info_indx].push_back(device_info.GetRemoteHandle(submit_info.pCommandBuffers[j]));
    }
    submit_info.commandBufferCount = command_buffers_remote[submit_info_indx].size();
    submit_info.pCommandBuffers = command_buffers_remote[submit_info_indx].data();

    submit_infos.emplace_back(std::move(submit_info));
  }

  {
    std::vector<VkPipelineStageFlags> wait_stages(semaphores_to_wait_local.size(), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
    std::vector<VkSemaphore> semaphores_to_wait_local_handles(semaphores_to_wait_local.size());
    for (size_t i = 0; i < semaphores_to_wait_local.size(); i++) {
      semaphores_to_wait_local_handles[i] = semaphores_to_wait_local[i]->local_handle;
    }
    VkFence aux_fence = device_info.fence_pool().GetFence();
    VkSubmitInfo local_semaphores_submit_info{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = nullptr,
        .waitSemaphoreCount = static_cast<uint32_t>(semaphores_to_wait_local_handles.size()),
        .pWaitSemaphores = semaphores_to_wait_local_handles.data(),
        .pWaitDstStageMask = wait_stages.data(),
        .commandBufferCount = 0,
        .pCommandBuffers = nullptr,
        .signalSemaphoreCount = 0,
        .pSignalSemaphores = nullptr,
    };
    device_info.dispatch_table().QueueSubmit(*device_info.present_queue(), 1, &local_semaphores_submit_info, aux_fence);
    std::thread remote_caller(
        [&dispatch_table = device_info.dispatch_table(), &command_stream = device_info.instance_info().command_stream(),
         remote_queue = device_info.GetRemoteHandle(queue), remote_fence = device_info.GetRemoteHandle(fence),
         local_fence = fence, &fence_pool = device_info.fence_pool(), aux_fence, device,
         remote_device = device_info.instance_info().GetRemoteHandle(device), submits = std::move(submit_infos),
         present_queue = *device_info.present_queue(), semaphores_to_wait_local = std::move(semaphores_to_wait_local),
         semaphores_to_signal = std::move(local_semaphores_to_signal_from_remote),
         // we need to move the vectors into this thread so they don't get deleted
         unused1 = std::move(semaphores_to_wait_remote), unused2 = std::move(semaphores_to_signal_remote),
         unused3 = std::move(command_buffers_remote)]() {
          // Wait for local semaphores
          spdlog::info("VkQueueSubmit: Waiting for local semaphores");
          VkResult result =
              dispatch_table.WaitForFences(device, 1, &aux_fence, VK_TRUE, kVkQueueSubmitLocalSemaphoreTimeout);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to wait for local semaphores");
          }
          result = dispatch_table.ResetFences(device, 1, &aux_fence);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to reset local fences");
          }
          fence_pool.ReturnFence(aux_fence);
          spdlog::info("VkQueueSubmit: Finished waiting for local semaphores");
          for (VkSemaphore semaphore : semaphores_to_wait_local) {
            semaphore->state = SemaphoreState::kUnsignaled;
          }

          // Then we can submit to the remote queue
          result = PackAndCallVkQueueSubmit(command_stream, remote_queue, submits.size(), submits.data(), remote_fence);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to submit to remote queue");
          }
          spdlog::info("VkQueueSubmit: Finished submitting to remote queue");

          // After that, we wait for the remote fence to be signaled, so we can signal the local fence
          result = PackAndCallVkWaitForFences(command_stream, remote_device, 1, &remote_fence, VK_TRUE,
                                              kVkQueueSubmitRemoteSemaphoreTimeout);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to wait for remote fence");
          }
          result = PackAndCallVkResetFences(command_stream, remote_device, 1, &remote_fence);
          if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to reset remote fences");
          }
          spdlog::info("VkQueueSubmit: Finished waiting for remote fence");
          dispatch_table.QueueSubmit(present_queue, 0, nullptr, local_fence);
          for (auto* semaphore : semaphores_to_signal) {
            semaphore->release();
          }
        });
    remote_caller.detach();
  }

  return VK_SUCCESS;
}
VKAPI_ATTR VkResult VKAPI_CALL DeviceWaitIdle(VkDevice device) {
  InstanceInfo& instance_info = GetInstanceInfo(device);
  return PackAndCallVkDeviceWaitIdle(instance_info.command_stream(), instance_info.GetRemoteHandle(device));
}
VKAPI_ATTR VkResult VKAPI_CALL QueueWaitIdle(VkQueue queue) {
  DeviceInfo& device_info = GetDeviceInfo(queue);
  return PackAndCallVkQueueWaitIdle(device_info.instance_info().command_stream(), device_info.GetRemoteHandle(queue));
}

VKAPI_ATTR void VKAPI_CALL CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask,
                                              VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
                                              uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers,
                                              uint32_t bufferMemoryBarrierCount,
                                              const VkBufferMemoryBarrier* pBufferMemoryBarriers,
                                              uint32_t imageMemoryBarrierCount,
                                              const VkImageMemoryBarrier* pImageMemoryBarriers) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdPipelineBarrier(device_info.instance_info().command_stream(),
                                  device_info.GetRemoteHandle(commandBuffer), srcStageMask, dstStageMask,
                                  dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount,
                                  pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage,
                                                VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount,
                                                const VkBufferImageCopy* pRegions) {
  DeviceInfo& device_info = GetDeviceInfo(commandBuffer);
  PackAndCallVkCmdCopyImageToBuffer(device_info.instance_info().command_stream(),
                                    device_info.GetRemoteHandle(commandBuffer), srcImage, srcImageLayout, dstBuffer,
                                    regionCount, pRegions);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice,
                                                        VkPhysicalDeviceProperties2* pProperties) {
  InstanceInfo& instance_info = GetInstanceInfo(physicalDevice);
  PackAndCallVkGetPhysicalDeviceProperties2(instance_info.command_stream(), physicalDevice, pProperties);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice,
                                                      VkPhysicalDeviceFeatures2* pFeatures) {
  InstanceInfo& instance_info = GetInstanceInfo(physicalDevice);
  PackAndCallVkGetPhysicalDeviceFeatures2(instance_info.command_stream(), physicalDevice, pFeatures);
}

VKAPI_ATTR VkResult VKAPI_CALL SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) {
  DeviceInfo& device_info = GetDeviceInfo(device);
  VkSemaphoreSignalInfo signal_info = *pSignalInfo;
  signal_info.semaphore = signal_info.semaphore->remote_handle;
  return PackAndCallVkSignalSemaphore(device_info.instance_info().command_stream(),
                                      device_info.instance_info().GetRemoteHandle(device), &signal_info);
}

}  // namespace vvk