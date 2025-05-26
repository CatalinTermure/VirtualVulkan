import copy
from xml.etree import ElementTree
from reg import Registry
from base_generator import BaseGeneratorOptions, Param
from vulkan_object import VulkanObject
from .vvk_generator import VvkGenerator
from .commons import first_letter_upper, COMMANDS_TO_GENERATE, get_required_function_definitions, fill_struct_from_proto, indent, TRIVIAL_TYPES


def log(*args):
    print("client_generator:", *args)


class ClientSrcGenerator(VvkGenerator):
    def __init__(self, base_vk: VulkanObject):
        VvkGenerator.__init__(self, base_vk)

    def get_function_prototype(self, func: str) -> str:
        (func_name, type_name) = func.split('/')
        if func_name == "FillProtoFromStruct":
            return f'void FillProtoFromStruct(vvk::server::{type_name}* proto, const {type_name}* original_struct);\n'
        return 'static_assert(false, "Unkown function type");\n'

    def generate_param(self, cmd_name: str, param: Param) -> tuple[str, str]:
        out = []
        after_call_code = []
        response_accessor = f'response.{cmd_name.lower()}()'
        command = self.vk.commands[cmd_name]
        if param.type in ['VkAllocationCallbacks']:
            return "", ""
        elif param.type in self.vk.enums:
            assert (not param.pointer and param.length is None)
            out.append(
                f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}(static_cast<vvk::server::{param.type}>({param.name}));\n')
        elif "Flags" in param.type or "FlagBits" in param.type:
            assert (not param.pointer and param.length is None)
            out.append(
                f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}({param.name});\n')
        elif param.pointer and param.const and param.type in self.vk.structs:
            if param.length is None:
                out.append(
                    f'  FillProtoFromStruct(request.mutable_{cmd_name.lower()}()->mutable_{param.name.lower()}(), {param.name});\n')
                self.required_functions.add(
                    f'FillProtoFromStruct/{param.type}')
            else:
                assert (param.length in [p.name for p in command.params])

                index_name = f'{param.name}_indx'
                out.append(
                    f'  for (uint32_t {index_name} = 0; {index_name} < {param.length}; {index_name}++) {{\n')
                out.append(
                    f'    FillProtoFromStruct(request.mutable_{cmd_name.lower()}()->add_{param.name.lower()}(), &{param.name}[{index_name}]);\n')
                self.required_functions.add(
                    f'FillProtoFromStruct/{param.type}')
                out.append("  }\n")
        elif param.pointer and param.const and param.type in self.vk.handles:
            if param.length is None:
                log("none length const pointer to handle:",
                    cmd_name, param.cDeclaration)
            else:
                assert (param.length in [
                    p.name for p in command.params])
                out.append(
                    f'  for (uint32_t i = 0; i < {param.length}; i++) {{\n')
                out.append(
                    f'    request.mutable_{cmd_name.lower()}()->add_{param.name.lower()}(reinterpret_cast<uint64_t>({param.name}[i]));\n')
                out.append("  }\n")
        elif param.pointer and param.const:
            if param.length is None:
                assert (param.type == 'char')
                out.append(
                    f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}({param.name});\n')
            else:
                if param.type in TRIVIAL_TYPES:
                    assert (param.length in [
                        p.name for p in command.params])
                    type_info = TRIVIAL_TYPES[param.type]
                    out.append(
                        f'  for (uint32_t i = 0; i < {param.length}; i++) {{\n')
                    if type_info.cast_to is None:
                        out.append(
                            f'    request.mutable_{cmd_name.lower()}()->add_{param.name.lower()}({param.name}[i]);\n')
                    else:
                        out.append(
                            f'    request.mutable_{cmd_name.lower()}()->add_{param.name.lower()}(static_cast<{type_info.cast_to}>({param.name}[i]));\n')
                    out.append("  }\n")
                else:
                    log("unknown const pointer type with length:",
                        cmd_name, param.cDeclaration)
        elif param.pointer and not param.const and param.type in self.vk.handles:
            if param.length is None:
                out.append(
                    f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}(reinterpret_cast<uint64_t>(*{param.name}));\n')
                after_call_code.append(
                    f'  *{param.name} = reinterpret_cast<{param.type}>({response_accessor}.{param.name.lower()}());\n')
            elif not param.optional:
                after_call_code.append(
                    f'  for (uint32_t i = 0; i < {param.length}; i++) {{\n')
                after_call_code.append(
                    f'    {param.name}[i] = reinterpret_cast<{param.type}>({response_accessor}.{param.name.lower()}(i));\n')
                after_call_code.append("  }\n")
            else:
                # only vkEnumerate* commands return multiple handles
                assert ("vkEnumerate" in cmd_name or cmd_name in [
                        "vkGetPhysicalDeviceQueueFamilyProperties"])

                out.append(f'  if ({param.name}) {{\n')
                out.append(
                    "    // the value we set is just a sentinel value, only its presence should be checked\n")
                out.append(
                    f'    request.mutable_{cmd_name.lower()}()->add_{param.name.lower()}(reinterpret_cast<uint64_t>({param.name}));\n')
                out.append("  } else {\n")
                out.append(
                    f'    request.mutable_{cmd_name.lower()}()->set_{param.length.lower()}(0);\n')
                out.append("  }\n")

                index_name = f'{param.name}_indx'
                after_call_code.append(f'  if ({param.name}) {{\n')
                after_call_code.append(
                    f'    assert(*{param.length} == {response_accessor}.{param.length.lower()}());\n')
                after_call_code.append(
                    f'    for (uint32_t {index_name} = 0; {index_name} < *{param.length}; {index_name}++) {{\n')
                after_call_code.append(
                    f'      {param.name}[{index_name}] = reinterpret_cast<{param.type}>({response_accessor}.{param.name.lower()}({index_name}));\n')
                after_call_code.append("    }\n")
                after_call_code.append("  }\n")
        elif param.pointer and not param.const and param.type in self.vk.structs:
            if param.length is None:
                # TODO: we may be sending too much data
                out.append(
                    f'  FillProtoFromStruct(request.mutable_{cmd_name.lower()}()->mutable_{param.name.lower()}(), {param.name});\n')
                self.required_functions.add(
                    f'FillProtoFromStruct/{param.type}')

                after_call_code.append(
                    f'  {param.type}& {param.name}_ref = *{param.name};\n')
                struct_fill_, unused = fill_struct_from_proto(
                    self, param.type, f'{param.name}_ref', f'{response_accessor}.{param.name.lower()}()', allow_alloc=False)
                assert (unused == "")
                after_call_code.append(struct_fill_)
            else:
                # only vkEnumerate* commands return multiple structs
                assert ("vkEnumerate" in cmd_name or cmd_name in [
                        "vkGetPhysicalDeviceQueueFamilyProperties"])
                assert (param.length in [p.name for p in command.params])

                out.append(f'  if ({param.name}) {{\n')
                out.append(
                    "    // the value we set is just a sentinel value, only its presence should be checked\n")
                out.append(
                    f'    auto* unused = request.mutable_{cmd_name.lower()}()->add_{param.name.lower()}();\n')
                out.append("  } else {\n")
                out.append(
                    f'    request.mutable_{cmd_name.lower()}()->set_{param.length.lower()}(0);\n')
                out.append("  }\n")

                index_name = f'{param.name}_indx'
                after_call_code.append(f'  if ({param.name}) {{\n')
                after_call_code.append(
                    f'    assert(*{param.length} == {response_accessor}.{param.length.lower()}());\n')
                after_call_code.append(
                    f'    for (uint32_t {index_name} = 0; {index_name} < *{param.length}; {index_name}++) {{\n')
                after_call_code.append(
                    f'      {param.type}& {param.name}_ref = {param.name}[{index_name}];\n')
                struct_fill_, unused = fill_struct_from_proto(
                    self, param.type, f'{param.name}_ref', f'{response_accessor}.{param.name.lower()}({index_name})', allow_alloc=False)
                assert (unused == "")
                after_call_code.append(indent(struct_fill_, 4))
                after_call_code.append("    }\n")
                after_call_code.append("  }\n")
        elif param.pointer and not param.const:
            if param.length is None:
                if param.name.startswith("pp"):
                    out.append(
                        f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}(reinterpret_cast<uint64_t>(*{param.name}));\n')
                    after_call_code.append(
                        f'  *{param.name} = reinterpret_cast<{param.type}*>({response_accessor}.{param.name.lower()}());\n')
                else:
                    out.append(
                        f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}(*{param.name});\n')
                    after_call_code.append(
                        f'  *{param.name} = {response_accessor}.{param.name.lower()}();\n')
            else:
                log("non zero length param:",
                    cmd_name, param.cDeclaration)
        elif param.type in self.vk.handles:
            out.append(
                f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}(reinterpret_cast<uint64_t>({param.name}));\n')
        elif param.type in TRIVIAL_TYPES:
            type_info = TRIVIAL_TYPES[param.type]
            if param.length is None:
                if type_info.cast_to is None:
                    out.append(
                        f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}({param.name});\n')
                else:
                    out.append(
                        f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}(static_cast<{type_info.cast_to}>({param.name}));\n')
            else:
                log("trivial type with non-zero length:",
                    cmd_name, param.cDeclaration)
        else:
            out.append(
                f"  // Unsupported param: {param.cDeclaration}\n")
            log("UNSUPPORTED PARAM:", cmd_name, param.cDeclaration)
        return "".join(out), "".join(after_call_code)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#include "remote_call.h"

#include "synchronized_bidi_stream.h"

#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>
#include "vvk_server.grpc.pb.h"
#include <cstring>

namespace vvk {
''')
        insert_function_definitions_index = len(out)

        for cmd_name in COMMANDS_TO_GENERATE:
            after_call_code = []
            command = self.vk.commands[cmd_name]
            params = ['VvkCommandClientBidiStream& stream']
            params.extend([param.cDeclaration.strip()
                          for param in command.params])
            out.append(
                f'{command.returnType} PackAndCall{first_letter_upper(cmd_name)}({", ".join(params)}) ')
            out.append("{\n")
            out.append("  vvk::server::VvkRequest request;\n")
            out.append(f'  request.set_method("{cmd_name}");\n')

            for param in command.params:
                if param.optional and "vkEnumerate" not in cmd_name and cmd_name not in ["vkGetPhysicalDeviceQueueFamilyProperties"] and param.type not in ['VkAllocationCallbacks']:
                    out.append(f'  if ({param.name}) {{\n')
                    out_, after_call_code_ = self.generate_param(
                        cmd_name, param)
                    out.append(indent(out_, 2))
                    out.append("  }\n")
                    after_call_code.append(after_call_code_)
                else:
                    out_, after_call_code_ = self.generate_param(
                        cmd_name, param)
                    out.append(out_)
                    after_call_code.append(after_call_code_)

            out.append("  vvk::server::VvkResponse response;\n")

            out.append('''
  if (!stream.Write(request)) {
    spdlog::error("Failed to write request to server");
  }
''')

            out.append('''
  if (!stream.Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
''')

            out.extend(after_call_code)

            if command.returnType == "VkResult":
                out.append(
                    f"  return static_cast<VkResult>(response.{cmd_name.lower()}().result());\n")
            elif command.returnType == 'void':
                pass
            else:
                log("UNHANDLED RETURN TYPE:", command.returnType)

            out.append("}\n")

        functions_to_generate = get_required_function_definitions(self)
        out[insert_function_definitions_index:insert_function_definitions_index] = \
            ["namespace {\n"] + \
            [func_def.splitlines()[0][:-2] + ";\n" for func_def in functions_to_generate] + \
            [func_def for func_def in functions_to_generate] + \
            ["}\n"]

        out.append("}  // namespace vvk\n")

        self.write("".join(out))


class ClientHeaderGenerator(VvkGenerator):
    def __init__(self, base_vk: VulkanObject):
        VvkGenerator.__init__(self, base_vk)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#ifndef VVK_COMMONS_REMOTE_CALL_H
#define VVK_COMMONS_REMOTE_CALL_H
#include "synchronized_bidi_stream.h"

#include "vulkan/vulkan_core.h"

#include <grpcpp/grpcpp.h>
#include "vvk_server.pb.h"

namespace vvk {
''')

        for cmd_name in COMMANDS_TO_GENERATE:
            command = self.vk.commands[cmd_name]
            params = ['VvkCommandClientBidiStream& stream']
            params.extend([param.cDeclaration.strip()
                          for param in command.params])
            out.append(
                f'{command.returnType} PackAndCall{first_letter_upper(cmd_name)}({", ".join(params)});\n')

        out.append("}  // namespace vvk\n")

        out.append("\n#endif  // VVK_COMMONS_REMOTE_CALL_H")

        self.write("".join(out))


def generate_client_src(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    opts = BaseGeneratorOptions(
        customFileName="remote_call.cpp",
        customDirectory="./commons",
    )
    gen = ClientSrcGenerator(base_vk)
    reg = Registry(gen, opts)
    reg.loadElementTree(vk_tree)
    reg.apiGen()


def generate_client_header(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    opts = BaseGeneratorOptions(
        customFileName="remote_call.h",
        customDirectory="./commons",
    )
    gen = ClientHeaderGenerator(base_vk)
    reg = Registry(gen, opts)
    reg.loadElementTree(vk_tree)
    reg.apiGen()


def generate_client(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    generate_client_header(vk_tree, base_vk)
    generate_client_src(vk_tree, base_vk)
