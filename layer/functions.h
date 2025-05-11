// GENERATED FILE - DO NOT EDIT
// clang-format off
#ifndef VVK_LAYER_FUNCTIONS_H
#define VVK_LAYER_FUNCTIONS_H

#include "layer/wsi_support.h"
#include <vulkan/vulkan.h>

#include <unordered_map>
#include <string>

namespace vvk {
PFN_vkVoidFunction DefaultGetInstanceProcAddr(VkInstance instance, const char* pName);
PFN_vkVoidFunction DefaultGetDeviceProcAddr(VkDevice device, const char* pName);

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(
    const VkInstanceCreateInfo*                 pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkInstance*                                 pInstance);
VKAPI_ATTR void VKAPI_CALL DestroyInstance(
    VkInstance                                  instance,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDevices(
    VkInstance                                  instance,
    uint32_t*                                   pPhysicalDeviceCount,
    VkPhysicalDevice*                           pPhysicalDevices);
VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceProperties(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties*                 pProperties);
VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFormatProperties(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkFormatProperties*                         pFormatProperties);
VKAPI_ATTR VkResult VKAPI_CALL CreateDevice(
    VkPhysicalDevice                            physicalDevice,
    const VkDeviceCreateInfo*                   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDevice*                                   pDevice);
VKAPI_ATTR void VKAPI_CALL DestroyDevice(
    VkDevice                                    device,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(
    const char*                                 pLayerName,
    uint32_t*                                   pPropertyCount,
    VkExtensionProperties*                      pProperties);
VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceExtensionProperties(
    VkPhysicalDevice                            physicalDevice,
    const char*                                 pLayerName,
    uint32_t*                                   pPropertyCount,
    VkExtensionProperties*                      pProperties);
VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceMemoryProperties(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceMemoryProperties*           pMemoryProperties);
VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFeatures(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures*                   pFeatures);
VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceQueueFamilyProperties(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties*                    pQueueFamilyProperties);
VKAPI_ATTR void VKAPI_CALL GetDeviceQueue(
    VkDevice                                    device,
    uint32_t                                    queueFamilyIndex,
    uint32_t                                    queueIndex,
    VkQueue*                                    pQueue);
VKAPI_ATTR VkResult VKAPI_CALL CreateFence(
    VkDevice                                    device,
    const VkFenceCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence);
VKAPI_ATTR void VKAPI_CALL DestroyFence(
    VkDevice                                    device,
    VkFence                                     fence,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL CreateSemaphore(
    VkDevice                                    device,
    const VkSemaphoreCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSemaphore*                                pSemaphore);
VKAPI_ATTR void VKAPI_CALL DestroySemaphore(
    VkDevice                                    device,
    VkSemaphore                                 semaphore,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL AllocateMemory(
    VkDevice                                    device,
    const VkMemoryAllocateInfo*                 pAllocateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDeviceMemory*                             pMemory);
VKAPI_ATTR void VKAPI_CALL FreeMemory(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL CreateImage(
    VkDevice                                    device,
    const VkImageCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkImage*                                    pImage);
VKAPI_ATTR void VKAPI_CALL DestroyImage(
    VkDevice                                    device,
    VkImage                                     image,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory(
    VkDevice                                    device,
    VkImage                                     image,
    VkDeviceMemory                              memory,
    VkDeviceSize                                memoryOffset);
VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory2(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindImageMemoryInfo*                pBindInfos);
VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements(
    VkDevice                                    device,
    VkImage                                     image,
    VkMemoryRequirements*                       pMemoryRequirements);
VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements2(
    VkDevice                                    device,
    const VkImageMemoryRequirementsInfo2*       pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements);
VKAPI_ATTR VkResult VKAPI_CALL CreateImageView(
    VkDevice                                    device,
    const VkImageViewCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkImageView*                                pView);
VKAPI_ATTR void VKAPI_CALL DestroyImageView(
    VkDevice                                    device,
    VkImageView                                 imageView,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL CreateCommandPool(
    VkDevice                                    device,
    const VkCommandPoolCreateInfo*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCommandPool*                              pCommandPool);
VKAPI_ATTR void VKAPI_CALL DestroyCommandPool(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL AllocateCommandBuffers(
    VkDevice                                    device,
    const VkCommandBufferAllocateInfo*          pAllocateInfo,
    VkCommandBuffer*                            pCommandBuffers);
VKAPI_ATTR void VKAPI_CALL FreeCommandBuffers(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    uint32_t                                    commandBufferCount,
    const VkCommandBuffer*                      pCommandBuffers);
VKAPI_ATTR VkResult VKAPI_CALL BeginCommandBuffer(
    VkCommandBuffer                             commandBuffer,
    const VkCommandBufferBeginInfo*             pBeginInfo);
VKAPI_ATTR VkResult VKAPI_CALL EndCommandBuffer(
    VkCommandBuffer                             commandBuffer);
VKAPI_ATTR void VKAPI_CALL GetImageSubresourceLayout(
    VkDevice                                    device,
    VkImage                                     image,
    const VkImageSubresource*                   pSubresource,
    VkSubresourceLayout*                        pLayout);
VKAPI_ATTR VkResult VKAPI_CALL CreateRenderPass(
    VkDevice                                    device,
    const VkRenderPassCreateInfo*               pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkRenderPass*                               pRenderPass);
VKAPI_ATTR void VKAPI_CALL DestroyRenderPass(
    VkDevice                                    device,
    VkRenderPass                                renderPass,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL CreatePipelineLayout(
    VkDevice                                    device,
    const VkPipelineLayoutCreateInfo*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPipelineLayout*                           pPipelineLayout);
VKAPI_ATTR void VKAPI_CALL DestroyPipelineLayout(
    VkDevice                                    device,
    VkPipelineLayout                            pipelineLayout,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL CreateShaderModule(
    VkDevice                                    device,
    const VkShaderModuleCreateInfo*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkShaderModule*                             pShaderModule);
VKAPI_ATTR void VKAPI_CALL DestroyShaderModule(
    VkDevice                                    device,
    VkShaderModule                              shaderModule,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL CreateGraphicsPipelines(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkGraphicsPipelineCreateInfo*         pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);
VKAPI_ATTR void VKAPI_CALL DestroyPipeline(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL CreateFramebuffer(
    VkDevice                                    device,
    const VkFramebufferCreateInfo*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFramebuffer*                              pFramebuffer);
VKAPI_ATTR void VKAPI_CALL DestroyFramebuffer(
    VkDevice                                    device,
    VkFramebuffer                               framebuffer,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL WaitForFences(
    VkDevice                                    device,
    uint32_t                                    fenceCount,
    const VkFence*                              pFences,
    VkBool32                                    waitAll,
    uint64_t                                    timeout);
VKAPI_ATTR VkResult VKAPI_CALL ResetFences(
    VkDevice                                    device,
    uint32_t                                    fenceCount,
    const VkFence*                              pFences);
VKAPI_ATTR VkResult VKAPI_CALL ResetCommandPool(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    VkCommandPoolResetFlags                     flags);
VKAPI_ATTR void VKAPI_CALL CmdBeginRenderPass(
    VkCommandBuffer                             commandBuffer,
    const VkRenderPassBeginInfo*                pRenderPassBegin,
    VkSubpassContents                           contents);
VKAPI_ATTR void VKAPI_CALL CmdEndRenderPass(
    VkCommandBuffer                             commandBuffer);
VKAPI_ATTR void VKAPI_CALL CmdBindPipeline(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipeline                                  pipeline);
VKAPI_ATTR void VKAPI_CALL CmdSetViewport(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkViewport*                           pViewports);
VKAPI_ATTR void VKAPI_CALL CmdSetScissor(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstScissor,
    uint32_t                                    scissorCount,
    const VkRect2D*                             pScissors);
VKAPI_ATTR void VKAPI_CALL CmdDraw(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    vertexCount,
    uint32_t                                    instanceCount,
    uint32_t                                    firstVertex,
    uint32_t                                    firstInstance);
VKAPI_ATTR VkResult VKAPI_CALL QueueSubmit(
    VkQueue                                     queue,
    uint32_t                                    submitCount,
    const VkSubmitInfo*                         pSubmits,
    VkFence                                     fence);
VKAPI_ATTR VkResult VKAPI_CALL DeviceWaitIdle(
    VkDevice                                    device);
VKAPI_ATTR VkResult VKAPI_CALL QueueWaitIdle(
    VkQueue                                     queue);
VKAPI_ATTR void VKAPI_CALL CmdPipelineBarrier(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags                        srcStageMask,
    VkPipelineStageFlags                        dstStageMask,
    VkDependencyFlags                           dependencyFlags,
    uint32_t                                    memoryBarrierCount,
    const VkMemoryBarrier*                      pMemoryBarriers,
    uint32_t                                    bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
    uint32_t                                    imageMemoryBarrierCount,
    const VkImageMemoryBarrier*                 pImageMemoryBarriers);
VKAPI_ATTR void VKAPI_CALL CmdCopyImageToBuffer(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkBuffer                                    dstBuffer,
    uint32_t                                    regionCount,
    const VkBufferImageCopy*                    pRegions);
VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceProperties2(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties2*                pProperties);
VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceFeatures2(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures2*                  pFeatures);
VKAPI_ATTR VkResult VKAPI_CALL SignalSemaphore(
    VkDevice                                    device,
    const VkSemaphoreSignalInfo*                pSignalInfo);
VKAPI_ATTR VkResult VKAPI_CALL CreateBuffer(
    VkDevice                                    device,
    const VkBufferCreateInfo*                   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkBuffer*                                   pBuffer);
VKAPI_ATTR void VKAPI_CALL DestroyBuffer(
    VkDevice                                    device,
    VkBuffer                                    buffer,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR void VKAPI_CALL GetBufferMemoryRequirements(
    VkDevice                                    device,
    VkBuffer                                    buffer,
    VkMemoryRequirements*                       pMemoryRequirements);
VKAPI_ATTR VkResult VKAPI_CALL BindBufferMemory(
    VkDevice                                    device,
    VkBuffer                                    buffer,
    VkDeviceMemory                              memory,
    VkDeviceSize                                memoryOffset);
VKAPI_ATTR VkResult VKAPI_CALL MapMemory(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkMemoryMapFlags                            flags,
    void**                                      ppData);
VKAPI_ATTR void VKAPI_CALL UnmapMemory(
    VkDevice                                    device,
    VkDeviceMemory                              memory);
VKAPI_ATTR void VKAPI_CALL CmdBindVertexBuffers(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets);
VKAPI_ATTR VkResult VKAPI_CALL CreateSwapchainKHR(
    VkDevice                                    device,
    const VkSwapchainCreateInfoKHR*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSwapchainKHR*                             pSwapchain);
VKAPI_ATTR void VKAPI_CALL DestroySwapchainKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainImagesKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint32_t*                                   pSwapchainImageCount,
    VkImage*                                    pSwapchainImages);
VKAPI_ATTR VkResult VKAPI_CALL AcquireNextImageKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint64_t                                    timeout,
    VkSemaphore                                 semaphore,
    VkFence                                     fence,
    uint32_t*                                   pImageIndex);
VKAPI_ATTR VkResult VKAPI_CALL QueuePresentKHR(
    VkQueue                                     queue,
    const VkPresentInfoKHR*                     pPresentInfo);
VKAPI_ATTR VkResult VKAPI_CALL CreateWaylandSurfaceKHR(
    VkInstance                                  instance,
    const VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
VKAPI_ATTR VkResult VKAPI_CALL CreateXcbSurfaceKHR(
    VkInstance                                  instance,
    const VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);
VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSurfaceSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    VkSurfaceKHR                                surface,
    VkBool32*                                   pSupported);

inline std::unordered_map<std::string, PFN_vkVoidFunction> g_name_to_func_ptr = {
    {"vkCreateInstance", reinterpret_cast<PFN_vkVoidFunction>(CreateInstance)},
    {"vkDestroyInstance", reinterpret_cast<PFN_vkVoidFunction>(DestroyInstance)},
    {"vkEnumeratePhysicalDevices", reinterpret_cast<PFN_vkVoidFunction>(EnumeratePhysicalDevices)},
    {"vkGetPhysicalDeviceProperties", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceProperties)},
    {"vkGetPhysicalDeviceFormatProperties", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceFormatProperties)},
    {"vkCreateDevice", reinterpret_cast<PFN_vkVoidFunction>(CreateDevice)},
    {"vkDestroyDevice", reinterpret_cast<PFN_vkVoidFunction>(DestroyDevice)},
    {"vkEnumerateInstanceExtensionProperties", reinterpret_cast<PFN_vkVoidFunction>(EnumerateInstanceExtensionProperties)},
    {"vkEnumerateDeviceExtensionProperties", reinterpret_cast<PFN_vkVoidFunction>(EnumerateDeviceExtensionProperties)},
    {"vkGetPhysicalDeviceMemoryProperties", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceMemoryProperties)},
    {"vkGetPhysicalDeviceFeatures", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceFeatures)},
    {"vkGetPhysicalDeviceQueueFamilyProperties", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceQueueFamilyProperties)},
    {"vkGetDeviceQueue", reinterpret_cast<PFN_vkVoidFunction>(GetDeviceQueue)},
    {"vkCreateFence", reinterpret_cast<PFN_vkVoidFunction>(CreateFence)},
    {"vkDestroyFence", reinterpret_cast<PFN_vkVoidFunction>(DestroyFence)},
    {"vkCreateSemaphore", reinterpret_cast<PFN_vkVoidFunction>(CreateSemaphore)},
    {"vkDestroySemaphore", reinterpret_cast<PFN_vkVoidFunction>(DestroySemaphore)},
    {"vkAllocateMemory", reinterpret_cast<PFN_vkVoidFunction>(AllocateMemory)},
    {"vkFreeMemory", reinterpret_cast<PFN_vkVoidFunction>(FreeMemory)},
    {"vkCreateImage", reinterpret_cast<PFN_vkVoidFunction>(CreateImage)},
    {"vkDestroyImage", reinterpret_cast<PFN_vkVoidFunction>(DestroyImage)},
    {"vkBindImageMemory", reinterpret_cast<PFN_vkVoidFunction>(BindImageMemory)},
    {"vkBindImageMemory2", reinterpret_cast<PFN_vkVoidFunction>(BindImageMemory2)},
    {"vkGetImageMemoryRequirements", reinterpret_cast<PFN_vkVoidFunction>(GetImageMemoryRequirements)},
    {"vkGetImageMemoryRequirements2", reinterpret_cast<PFN_vkVoidFunction>(GetImageMemoryRequirements2)},
    {"vkCreateImageView", reinterpret_cast<PFN_vkVoidFunction>(CreateImageView)},
    {"vkDestroyImageView", reinterpret_cast<PFN_vkVoidFunction>(DestroyImageView)},
    {"vkCreateCommandPool", reinterpret_cast<PFN_vkVoidFunction>(CreateCommandPool)},
    {"vkDestroyCommandPool", reinterpret_cast<PFN_vkVoidFunction>(DestroyCommandPool)},
    {"vkAllocateCommandBuffers", reinterpret_cast<PFN_vkVoidFunction>(AllocateCommandBuffers)},
    {"vkFreeCommandBuffers", reinterpret_cast<PFN_vkVoidFunction>(FreeCommandBuffers)},
    {"vkBeginCommandBuffer", reinterpret_cast<PFN_vkVoidFunction>(BeginCommandBuffer)},
    {"vkEndCommandBuffer", reinterpret_cast<PFN_vkVoidFunction>(EndCommandBuffer)},
    {"vkGetImageSubresourceLayout", reinterpret_cast<PFN_vkVoidFunction>(GetImageSubresourceLayout)},
    {"vkCreateRenderPass", reinterpret_cast<PFN_vkVoidFunction>(CreateRenderPass)},
    {"vkDestroyRenderPass", reinterpret_cast<PFN_vkVoidFunction>(DestroyRenderPass)},
    {"vkCreatePipelineLayout", reinterpret_cast<PFN_vkVoidFunction>(CreatePipelineLayout)},
    {"vkDestroyPipelineLayout", reinterpret_cast<PFN_vkVoidFunction>(DestroyPipelineLayout)},
    {"vkCreateShaderModule", reinterpret_cast<PFN_vkVoidFunction>(CreateShaderModule)},
    {"vkDestroyShaderModule", reinterpret_cast<PFN_vkVoidFunction>(DestroyShaderModule)},
    {"vkCreateGraphicsPipelines", reinterpret_cast<PFN_vkVoidFunction>(CreateGraphicsPipelines)},
    {"vkDestroyPipeline", reinterpret_cast<PFN_vkVoidFunction>(DestroyPipeline)},
    {"vkCreateFramebuffer", reinterpret_cast<PFN_vkVoidFunction>(CreateFramebuffer)},
    {"vkDestroyFramebuffer", reinterpret_cast<PFN_vkVoidFunction>(DestroyFramebuffer)},
    {"vkWaitForFences", reinterpret_cast<PFN_vkVoidFunction>(WaitForFences)},
    {"vkResetFences", reinterpret_cast<PFN_vkVoidFunction>(ResetFences)},
    {"vkResetCommandPool", reinterpret_cast<PFN_vkVoidFunction>(ResetCommandPool)},
    {"vkCmdBeginRenderPass", reinterpret_cast<PFN_vkVoidFunction>(CmdBeginRenderPass)},
    {"vkCmdEndRenderPass", reinterpret_cast<PFN_vkVoidFunction>(CmdEndRenderPass)},
    {"vkCmdBindPipeline", reinterpret_cast<PFN_vkVoidFunction>(CmdBindPipeline)},
    {"vkCmdSetViewport", reinterpret_cast<PFN_vkVoidFunction>(CmdSetViewport)},
    {"vkCmdSetScissor", reinterpret_cast<PFN_vkVoidFunction>(CmdSetScissor)},
    {"vkCmdDraw", reinterpret_cast<PFN_vkVoidFunction>(CmdDraw)},
    {"vkQueueSubmit", reinterpret_cast<PFN_vkVoidFunction>(QueueSubmit)},
    {"vkDeviceWaitIdle", reinterpret_cast<PFN_vkVoidFunction>(DeviceWaitIdle)},
    {"vkQueueWaitIdle", reinterpret_cast<PFN_vkVoidFunction>(QueueWaitIdle)},
    {"vkCmdPipelineBarrier", reinterpret_cast<PFN_vkVoidFunction>(CmdPipelineBarrier)},
    {"vkCmdCopyImageToBuffer", reinterpret_cast<PFN_vkVoidFunction>(CmdCopyImageToBuffer)},
    {"vkGetPhysicalDeviceProperties2", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceProperties2)},
    {"vkGetPhysicalDeviceFeatures2", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceFeatures2)},
    {"vkSignalSemaphore", reinterpret_cast<PFN_vkVoidFunction>(SignalSemaphore)},
    {"vkCreateBuffer", reinterpret_cast<PFN_vkVoidFunction>(CreateBuffer)},
    {"vkDestroyBuffer", reinterpret_cast<PFN_vkVoidFunction>(DestroyBuffer)},
    {"vkGetBufferMemoryRequirements", reinterpret_cast<PFN_vkVoidFunction>(GetBufferMemoryRequirements)},
    {"vkBindBufferMemory", reinterpret_cast<PFN_vkVoidFunction>(BindBufferMemory)},
    {"vkMapMemory", reinterpret_cast<PFN_vkVoidFunction>(MapMemory)},
    {"vkUnmapMemory", reinterpret_cast<PFN_vkVoidFunction>(UnmapMemory)},
    {"vkCmdBindVertexBuffers", reinterpret_cast<PFN_vkVoidFunction>(CmdBindVertexBuffers)},
    {"vkCreateSwapchainKHR", reinterpret_cast<PFN_vkVoidFunction>(CreateSwapchainKHR)},
    {"vkDestroySwapchainKHR", reinterpret_cast<PFN_vkVoidFunction>(DestroySwapchainKHR)},
    {"vkGetSwapchainImagesKHR", reinterpret_cast<PFN_vkVoidFunction>(GetSwapchainImagesKHR)},
    {"vkAcquireNextImageKHR", reinterpret_cast<PFN_vkVoidFunction>(AcquireNextImageKHR)},
    {"vkQueuePresentKHR", reinterpret_cast<PFN_vkVoidFunction>(QueuePresentKHR)},
    {"vkCreateWaylandSurfaceKHR", reinterpret_cast<PFN_vkVoidFunction>(CreateWaylandSurfaceKHR)},
    {"vkCreateXcbSurfaceKHR", reinterpret_cast<PFN_vkVoidFunction>(CreateXcbSurfaceKHR)},
    {"vkGetPhysicalDeviceSurfaceSupportKHR", reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceSurfaceSupportKHR)},
};

}  // namespace vvk

#endif  // VVK_LAYER_FUNCTIONS_H
