// GENERATED FILE - DO NOT EDIT
// clang-format off
#include "vulkan/vulkan_core.h"

#include <grpcpp/grpcpp.h>
#include "vvk_server.pb.h"

namespace vvk {
VkResult PackAndCallVkCreateInstance(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
void PackAndCallVkDestroyInstance(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkInstance instance, const VkAllocationCallbacks* pAllocator);
VkResult PackAndCallVkEnumeratePhysicalDevices(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
void PackAndCallVkGetPhysicalDeviceProperties(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties);
VkResult PackAndCallVkCreateDevice(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);
void PackAndCallVkDestroyDevice(grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream, VkDevice device, const VkAllocationCallbacks* pAllocator);
}  // namespace vvk

