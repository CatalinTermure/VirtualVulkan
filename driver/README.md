# VirtualVulkan Driver

This is a Vulkan Installable Client Driver(ICD) that implements Vulkan API calls by sending them to a remote server.

This ICD does NOT support presentation. On Linux, you may use a layer like Mesa's [Vulkan WSI Layer](https://gitlab.freedesktop.org/mesa/vulkan-wsi-layer) that can add presentation support to any ICD.