from xml.etree import ElementTree
from reg import Registry
from base_generator import BaseGeneratorOptions
from vulkan_object import VulkanObject
from .vvk_generator import VvkGenerator
from .commons import COMMANDS_TO_GENERATE


class ClientHeaderGenerator(VvkGenerator):
    def __init__(self, base_vk: VulkanObject):
        VvkGenerator.__init__(self, base_vk)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#ifndef VVK_LAYER_FUNCTIONS_H
#define VVK_LAYER_FUNCTIONS_H

#include "layer/wsi_support.h"
#include <vulkan/vulkan.h>

#include <unordered_map>
#include <string>

namespace vvk {
PFN_vkVoidFunction DefaultGetInstanceProcAddr(VkInstance instance, const char* pName);
PFN_vkVoidFunction DefaultGetDeviceProcAddr(VkDevice device, const char* pName);

''')
        name_to_func_ptr_map = [
            'inline std::unordered_map<std::string, PFN_vkVoidFunction> g_name_to_func_ptr = {\n'
        ]

        PROTOTYPES_TO_GENERATE = ["vkCreateSwapchainKHR", "vkDestroySwapchainKHR",
                                  "vkGetSwapchainImagesKHR", "vkAcquireNextImageKHR",
                                  "vkQueuePresentKHR", "vkCreateWaylandSurfaceKHR",
                                  "vkGetPhysicalDeviceSurfaceSupportKHR"]

        for cmd_name in COMMANDS_TO_GENERATE + PROTOTYPES_TO_GENERATE:
            name_to_func_ptr_map.append(
                f'    {"{"}"{cmd_name}", reinterpret_cast<PFN_vkVoidFunction>({cmd_name[2:]}){"}"},\n')
            out.append(self.vk.commands[cmd_name].cPrototype.replace(
                cmd_name, cmd_name[2:]))
            out.append("\n")

        out.append("\n")
        out.extend(name_to_func_ptr_map)
        out.append("};\n\n")

        out.append("}  // namespace vvk\n")

        out.append("\n#endif  // VVK_LAYER_FUNCTIONS_H")

        self.write("".join(out))


def generate_functions_header(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    opts = BaseGeneratorOptions(
        customFileName="functions.h",
        customDirectory="./layer",
    )
    gen = ClientHeaderGenerator(base_vk)
    reg = Registry(gen, opts)
    reg.loadElementTree(vk_tree)
    reg.apiGen()


def generate_layer(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    generate_functions_header(vk_tree, base_vk)
