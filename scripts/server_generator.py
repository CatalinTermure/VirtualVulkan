from xml.etree import ElementTree
from reg import Registry
from base_generator import BaseGeneratorOptions
from vulkan_object import VulkanObject
from .vvk_generator import VvkGenerator
from .commons import first_letter_upper, COMMANDS_TO_GENERATE, fill_struct_from_proto, get_required_function_definitions, indent, TRIVIAL_TYPES


def log(*args):
    print("server_generator:", *args)


class ServerSrcGenerator(VvkGenerator):
    def __init__(self, base_vk: VulkanObject):
        VvkGenerator.__init__(self, base_vk)

    def c_to_proto_accessor(self, c_accessor: str) -> str:
        # a->b->c -> a().b().c()
        return c_accessor.lower().replace("->", "().") + "()"

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#include "implementations.h"

#include <vulkan/vulkan.h>

#include <cassert>
#include <unordered_map>
#include <vector>
#include <cstdlib>

#include "server/execution_context.h"

''')

        insert_function_definitions_index = len(out)

        for cmd_name in COMMANDS_TO_GENERATE:
            after_call_code = []
            deletions = []
            actual_parameters = []
            out.append(
                f'void UnpackAndExecute{first_letter_upper(cmd_name)}(vvk::ExecutionContext& context, const vvk::server::VvkRequest& request, vvk::server::VvkResponse* response)')
            out.append("{\n")
            out.append(f'  assert(request.method() == "{cmd_name}");\n\n')
            param_accessor = f'request.{cmd_name.lower()}()'
            command = self.vk.commands[cmd_name]
            for param in command.params:
                if param.type in ["VkAllocationCallbacks"]:
                    actual_parameters.append("nullptr")
                    continue
                elif param.type in self.vk.enums:
                    assert (not param.pointer and param.length is None)
                    actual_parameters.append(
                        f'static_cast<{param.type}>({param_accessor}.{param.name.lower()}())')
                elif "Flags" in param.type or "FlagBits" in param.type:
                    assert (not param.pointer and param.length is None)
                    actual_parameters.append(
                        f'static_cast<{param.type}>({param_accessor}.{param.name.lower()}())')
                elif param.const and param.pointer and param.type in self.vk.structs:
                    if param.length is None:
                        actual_parameters.append(f'&{param.name}')
                        out.append(f'  {param.type} {param.name} = {{}};\n')
                        out_, after_ = fill_struct_from_proto(self,
                                                              param.type, param.name, f'{param_accessor}.{param.name.lower()}()')
                        out.append(out_)
                        deletions.append(after_)
                    else:
                        assert (param.length in [
                                p.name for p in command.params])
                        actual_parameters.append(f'{param.name}.data()')
                        out.append(
                            f'  std::vector<{param.type}> {param.name}({param_accessor}.{param.length.lower()}());\n')
                        out.append(
                            f'  for (int i = 0; i < {param.name}.size(); i++) {{\n')
                        out.append(
                            f'    {param.type}& {param.name}_ref = {param.name}[i];\n')
                        out_, after_ = fill_struct_from_proto(self,
                                                              param.type, f'{param.name}_ref', f'{param_accessor}.{param.name.lower()}(i)')
                        out.append(indent(out_, 2))
                        out.append("  }\n")
                        if after_:
                            deletions.append(
                                f'  for (int i = 0; i < {param.name}.size(); i++) {{\n')
                            deletions.append(
                                f'    {param.type}& {param.name}_ref = {param.name}[i];\n')
                            deletions.append(indent(after_, 2))
                            deletions.append("  }\n")
                elif param.const and param.pointer:
                    if param.length is None:
                        assert (param.type == 'char')
                        actual_parameters.append(
                            f'{param_accessor}.{param.name.lower()}().data()')
                    else:
                        assert (param.type in self.vk.handles)
                        actual_parameters.append(
                            f'reinterpret_cast<const {param.type}*>({param_accessor}.{param.name.lower()}().data())')
                elif param.pointer and not param.const and param.type in self.vk.handles:
                    if param.length is None:
                        actual_parameters.append(f'&server_{param.name}')
                        out.append(
                            f'  {param.type} client_{param.name} = reinterpret_cast<{param.type}>({param_accessor}.{param.name.lower()}());\n')
                        out.append(f'  {param.type} server_{param.name};\n')
                        after_call_code.append(
                            f'  response->mutable_{cmd_name.lower()}()->set_{param.name.lower()}(reinterpret_cast<uint64_t>(server_{param.name}));\n')
                    elif not param.optional:
                        param_length_accessor = self.c_to_proto_accessor(
                            param.length)
                        out.append(
                            f'  std::vector<{param.type}> {param.name}({param_accessor}.{param_length_accessor});\n')
                        actual_parameters.append(f'{param.name}.data()')

                        after_call_code.append(
                            f'  for ({param.type} {param.name}_elem : {param.name}) {{\n')
                        after_call_code.append(
                            f'    response->mutable_{cmd_name.lower()}()->add_{param.name.lower()}(reinterpret_cast<uint64_t>({param.name}_elem));\n')
                        after_call_code.append("  }\n")
                    else:
                        # only vkEnumerate* commands return multiple handles
                        assert ("vkEnumerate" in cmd_name or cmd_name in [
                            "vkGetPhysicalDeviceQueueFamilyProperties"])
                        assert (param.length in [
                                p.name for p in command.params])
                        actual_parameters.append(f'{param.name}')
                        length_param = [
                            p for p in command.params if p.name == param.length][0]
                        # this vector will live long enough
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

                        index_name = f'{param.name}_index'
                        after_call_code.append(
                            f'  if ({param_accessor}.{length_param.name.lower()}() != 0) {{\n')
                        after_call_code.append(
                            f'    for (int {index_name} = 0; {index_name} < {length_param.name}; {index_name}++) {{\n')
                        after_call_code.append(
                            f'      response->mutable_{cmd_name.lower()}()->add_{param.name.lower()}(reinterpret_cast<uint64_t>({param.name}[{index_name}]));\n')
                        after_call_code.append("    }\n")
                        after_call_code.append("  }\n")
                elif param.pointer and not param.const and param.type in self.vk.structs:
                    if param.length is None:
                        actual_parameters.append(f'&{param.name}')

                        out.append(f'  {param.type} {param.name} = {{}};\n')
                        struct_type = self.vk.structs[param.type]
                        if struct_type.sType is not None:
                            out.append(
                                f'  {param.name}.sType = {self.vk.structs[param.type].sType};\n')

                        after_call_code.append(
                            f'  FillProtoFromStruct(response->mutable_{cmd_name.lower()}()->mutable_{param.name.lower()}(), &{param.name});\n')
                        self.required_functions.add(
                            f'FillProtoFromStruct/{param.type}')
                    else:
                        # only vkEnumerate* commands return multiple structs
                        assert ("vkEnumerate" in cmd_name or cmd_name in [
                            "vkGetPhysicalDeviceQueueFamilyProperties"])
                        assert (param.length in [
                                p.name for p in command.params])
                        actual_parameters.append(f'{param.name}')
                        length_param = [
                            p for p in command.params if p.name == param.length][0]
                        # this vector will live long enough
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

                        index_name = f'{param.name}_index'
                        after_call_code.append(
                            f'  if ({param_accessor}.{length_param.name.lower()}() != 0) {{\n')
                        after_call_code.append(
                            f'    for (int {index_name} = 0; {index_name} < {length_param.name}; {index_name}++) {{\n')
                        after_call_code.append(
                            f'      FillProtoFromStruct(response->mutable_{cmd_name.lower()}()->add_{param.name.lower()}(), &{param.name}[{index_name}]);\n')
                        self.required_functions.add(
                            f'FillProtoFromStruct/{param.type}')
                        after_call_code.append("    }\n")
                        after_call_code.append("  }\n")
                elif param.pointer and not param.const:
                    actual_parameters.append(f'&{param.name}')
                    out.append(
                        f'  {param.type} {param.name} = {param_accessor}.{param.name.lower()}();\n')
                    after_call_code.append(
                        f'  response->mutable_{cmd_name.lower()}()->set_{param.name.lower()}({param.name});\n')
                elif not param.pointer and param.type in self.vk.handles:
                    if param.type == "VkPhysicalDevice":
                        actual_parameters.append("context.physical_device()")
                    else:
                        actual_parameters.append(
                            f'reinterpret_cast<{param.type}>({param_accessor}.{param.name.lower()}())')
                elif param.type in TRIVIAL_TYPES:
                    type_info = TRIVIAL_TYPES[param.type]
                    if param.length is None:
                        if type_info.cast_to is None:
                            actual_parameters.append(
                                f'{param_accessor}.{param.name.lower()}()')
                        else:
                            actual_parameters.append(
                                f'static_cast<{param.type}>({param_accessor}.{param.name.lower()}())')
                    else:
                        log("trivial type with non-zero length:",
                            cmd_name, param.cDeclaration)
                else:
                    log("UNHANDLED PARAM:", cmd_name, param.name)

            # call the function
            if command.returnType == "VkResult":
                out.append(f'  VkResult result = {cmd_name}(')
            elif command.returnType == "void":
                out.append(f'  {cmd_name}(')
            else:
                log("UNHANDLED RETURN TYPE:", command.returnType)

            out.append(", ".join(actual_parameters))
            out.append(");\n")

            out.extend(after_call_code)

            # populate the response
            if command.returnType == "VkResult":
                out.append("  response->set_result(result);\n")
            elif command.returnType == "void":
                out.append("  response->set_result(VK_SUCCESS);\n")

            out.extend(deletions)
            out.append("}\n")

        functions_to_generate = get_required_function_definitions(self)
        out[insert_function_definitions_index:insert_function_definitions_index] = \
            ["namespace {\n"] + \
            [func_def.splitlines()[0][:-2] + ";\n" for func_def in functions_to_generate] + \
            [func_def for func_def in functions_to_generate] + \
            ["}\n"]

        self.write("".join(out))


class ServerHeaderGenerator(VvkGenerator):
    def __init__(self, base_vk: VulkanObject):
        VvkGenerator.__init__(self, base_vk)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#ifndef VVK_SERVER_IMPLEMENTATIONS_H
#define VVK_SERVER_IMPLEMENTATIONS_H
#include <vulkan/vulkan_core.h>

#include "server/execution_context.h"
#include "vvk_server.pb.h"

''')

        for command in COMMANDS_TO_GENERATE:
            out.append(
                f'''void UnpackAndExecute{first_letter_upper(command)}(vvk::ExecutionContext& context,
                                      const vvk::server::VvkRequest &request, vvk::server::VvkResponse* response);''')
            if command != COMMANDS_TO_GENERATE[-1]:
                out.append("\n")

        out.append("\n#endif  // VVK_SERVER_IMPLEMENTATIONS_H")
        self.write("".join(out))


def generate_server_src(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    opts = BaseGeneratorOptions(
        customFileName="implementations.cpp",
        customDirectory="./server",
    )
    gen = ServerSrcGenerator(base_vk)
    reg = Registry(gen, opts)
    reg.loadElementTree(vk_tree)
    reg.apiGen()


def generate_server_header(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    opts = BaseGeneratorOptions(
        customFileName="implementations.h",
        customDirectory="./server",
    )
    gen = ServerHeaderGenerator(base_vk)
    reg = Registry(gen, opts)
    reg.loadElementTree(vk_tree)
    reg.apiGen()


def generate_server(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    generate_server_header(vk_tree, base_vk)
    generate_server_src(vk_tree, base_vk)
