from xml.etree import ElementTree
from reg import Registry
from generators.base_generator import BaseGenerator, BaseGeneratorOptions, SetTargetApiName, SetMergedApiNames
from .commons import first_letter_upper, COMMANDS_TO_GENERATE


class ClientHeaderGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#include <vulkan/vulkan_core.h>

#include <unordered_map>
#include <string>

namespace vvk {

''')
        name_to_func_ptr_map = [
            'inline std::unordered_map<std::string, PFN_vkVoidFunction> g_name_to_func_ptr = {\n'
        ]

        for cmd_name in COMMANDS_TO_GENERATE:
            name_to_func_ptr_map.append(
                f'    {"{"}"{cmd_name}", reinterpret_cast<PFN_vkVoidFunction>({cmd_name[2:]}){"}"},\n')
            out.append(self.vk.commands[cmd_name].cPrototype.replace(
                cmd_name, cmd_name[2:]))
            out.append("\n")

        out.append("\n")
        out.extend(name_to_func_ptr_map)
        out.append("};\n\n")

        out.append("}  // namespace vvk\n")

        self.write("".join(out))


def generate_functions_header():
    SetTargetApiName('vulkan')
    SetMergedApiNames('vulkan')
    opts = BaseGeneratorOptions(
        customFileName="functions.h",
        customDirectory="./layer",
    )
    gen = ClientHeaderGenerator()
    reg = Registry(gen, opts)
    tree = ElementTree.parse("./Vulkan-Headers/registry/vk.xml")
    reg.loadElementTree(tree)
    reg.apiGen()


def generate_layer():
    generate_functions_header()
