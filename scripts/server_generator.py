from xml.etree import ElementTree
from reg import Registry
from generators.base_generator import BaseGenerator, BaseGeneratorOptions, SetTargetApiName, SetMergedApiNames
from .commons import first_letter_upper, COMMANDS_TO_GENERATE, fill_proto_from_struct, fill_struct_from_proto


def log(*args):
    print("server_generator:", *args)


class ServerSrcGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#include "implementations.h"

#include <vulkan/vulkan.h>

#include <cassert>
#include <unordered_map>
#include <vector>

namespace {
std::unordered_map<void*, void*> client_to_server_handles;
VkPhysicalDevice physical_device_to_use;
}

void SetPhysicalDevice(VkPhysicalDevice physical_device) {
  physical_device_to_use = physical_device;
}

''')

        for cmd_name in COMMANDS_TO_GENERATE:
            after_call_code = []
            actual_parameters = []
            out.append(
                f'''void UnpackAndExecute{first_letter_upper(cmd_name)}(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response) ''')
            out.append("{\n")
            out.append(f'  assert(request.method() == "{cmd_name}");\n\n')
            param_accessor = f'request.{cmd_name.lower()}()'
            command = self.vk.commands[cmd_name]
            for param in command.params:
                if param.type in ["VkAllocationCallbacks"]:
                    actual_parameters.append("nullptr")
                    continue
                elif param.const and param.pointer:
                    actual_parameters.append(f'&{param.name}')
                    if param.length is None:
                        out.append(f'  {param.type} {param.name};\n')
                        out.append(fill_struct_from_proto(self,
                                                          param.type, param.name, f'{param_accessor}.{param.name.lower()}()'))
                    else:
                        log("non zero length param:",
                            cmd_name, param.cDeclaration)
                elif param.pointer and not param.const and param.type in self.vk.handles:
                    if param.length is None:
                        actual_parameters.append(f'&server_{param.name}')
                        out.append(
                            f'  {param.type} client_{param.name} = reinterpret_cast<{param.type}>({param_accessor}.{param.name.lower()}());\n')
                        out.append(f'  {param.type} server_{param.name};\n')
                        after_call_code.append(
                            f'  assert(client_to_server_handles.count(reinterpret_cast<void*>(client_{param.name})) == 0);\n')
                        after_call_code.append(
                            f'  response->mutable_{cmd_name.lower()}()->set_{param.name.lower()}(reinterpret_cast<uint64_t>(server_{param.name}));\n')
                        after_call_code.append(
                            f'  client_to_server_handles[client_{param.name}] = server_{param.name};\n')
                    else:
                        # only vkEnumerate* commands return multiple handles
                        assert ("vkEnumerate" in cmd_name)
                        assert (param.length in [
                                p.name for p in command.params])
                        actual_parameters.append(f'{param.name}')
                        length_param = [
                            p for p in command.params if p.name == param.length][0]
                        out.append(
                            f'  std::vector<{param.type}> aux_{param.name};\n')
                        out.append(f'  {param.type}* {param.name};\n')
                        out.append(
                            f'  if ({length_param.name} == 0) {{\n')
                        out.append(f'    {param.name} = nullptr;\n')
                        out.append("  } else {\n")
                        out.append(
                            f'    aux_{param.name}.resize({length_param.name});\n')
                        out.append(
                            f'    {param.name} = aux_{param.name}.data();\n')
                        out.append("  }\n")

                        after_call_code.append(
                            f'  if ({param_accessor}.{length_param.name.lower()}() != 0) {{\n')
                        after_call_code.append(
                            f'    for (int i = 0; i < {length_param.name}; i++) {{\n')
                        after_call_code.append(
                            f'      response->mutable_{cmd_name.lower()}()->add_{param.name.lower()}(reinterpret_cast<uint64_t>({param.name}[i]));\n')
                        after_call_code.append("    }\n")
                        after_call_code.append("  }\n")
                elif param.pointer and not param.const and param.type in self.vk.structs:
                    actual_parameters.append(f'&{param.name}')

                    out.append(f'  {param.type} {param.name};\n')

                    after_call_code.append(
                        f'  vvk::server::{param.type}* {param.name}_proto = response->mutable_{cmd_name.lower()}()->mutable_{param.name.lower()}();\n')
                    after_call_code.append(fill_proto_from_struct(
                        self, param.type, f'{param.name}_proto', f'(&{param.name})'))

                elif param.pointer and not param.const:
                    actual_parameters.append(f'&{param.name}')
                    out.append(
                        f'  {param.type} {param.name} = {param_accessor}.{param.name.lower()}();\n')
                    after_call_code.append(
                        f'  response->mutable_{cmd_name.lower()}()->set_{param.name.lower()}({param.name});\n')
                elif not param.pointer and param.type in self.vk.handles:
                    if param.type == "VkPhysicalDevice":
                        actual_parameters.append("physical_device_to_use")
                    else:
                        actual_parameters.append(
                            f'reinterpret_cast<{param.type}>(client_to_server_handles.at(reinterpret_cast<void*>({param_accessor}.{param.name.lower()}())))')
                else:
                    log("UNHANDLED PARAM:", cmd_name, param.name)

            # call the function
            if command.returnType == "VkResult":
                out.append(f'  VkResult result = {cmd_name}(')
            elif command.returnType == "void":
                out.append(f'  {cmd_name}(')

            out.append(", ".join(actual_parameters))
            out.append(");\n")

            out.extend(after_call_code)

            if "vkDestroy" in cmd_name:
                out.append(
                    f'  client_to_server_handles.erase(reinterpret_cast<void*>({param_accessor}.{command.params[0].name.lower()}()));\n')

            # populate the response
            if command.returnType == "VkResult":
                out.append("  response->set_result(result);\n")
            elif command.returnType == "void":
                out.append("  response->set_result(VK_SUCCESS);\n")

            out.append("}\n")

        self.write("".join(out))


class ServerHeaderGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#include "vvk_server.pb.h"
#include <vulkan/vulkan_core.h>

void SetPhysicalDevice(VkPhysicalDevice physical_device);
''')

        for command in COMMANDS_TO_GENERATE:
            out.append(
                f'''void UnpackAndExecute{first_letter_upper(command)}(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response);{"\n" if command != COMMANDS_TO_GENERATE[-1] else ""}''')

        self.write("".join(out))


def generate_server_src():
    SetTargetApiName('vulkan')
    SetMergedApiNames('vulkan')
    opts = BaseGeneratorOptions(
        customFileName="implementations.cpp",
        customDirectory="./server",
    )
    gen = ServerSrcGenerator()
    reg = Registry(gen, opts)
    tree = ElementTree.parse("./Vulkan-Headers/registry/vk.xml")
    reg.loadElementTree(tree)
    reg.apiGen()


def generate_server_header():
    SetTargetApiName('vulkan')
    SetMergedApiNames('vulkan')
    opts = BaseGeneratorOptions(
        customFileName="implementations.h",
        customDirectory="./server",
    )
    gen = ServerHeaderGenerator()
    reg = Registry(gen, opts)
    tree = ElementTree.parse("./Vulkan-Headers/registry/vk.xml")
    reg.loadElementTree(tree)
    reg.apiGen()


def generate_server():
    generate_server_header()
    generate_server_src()
