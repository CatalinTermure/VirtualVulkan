from xml.etree import ElementTree
from reg import Registry
from generators.base_generator import BaseGenerator, BaseGeneratorOptions, SetTargetApiName, SetMergedApiNames
from .commons import first_letter_upper, COMMANDS_TO_GENERATE

TRIVIAL_TYPES = [
    "uint32_t",
    "VkBool32",
]


def log(*args):
    print("client_generator:", *args)


class ClientSrcGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def fill_proto_from_struct(self, struct_type: str, name: str, struct_accessor: str) -> str:
        out = []
        struct = self.vk.structs[struct_type]
        for member in struct.members:
            if member.name in ['sType']:
                continue
            elif member.name == 'pNext':
                out.append("  // pNext chains are currently not supported\n")
            elif member.type in TRIVIAL_TYPES:
                out.append(
                    f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
            elif "Flags" in member.type:
                out.append(
                    f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
            elif member.pointer and member.const and member.type in self.vk.structs:
                if member.length is None:
                    out.append(
                        f'  vvk::server::{member.type}* {name}_{member.name}_proto = {name}->mutable_{member.name.lower()}();\n')
                    out.append(self.fill_proto_from_struct(
                        member.type, f'{name}_{member.name}_proto', f'{struct_accessor}->{member.name}'))
                else:
                    log("non zero length member:",
                        struct_type, member.cDeclaration)
            elif 'const char* const*' in member.cDeclaration:
                if member.length in [member.name for member in struct.members]:
                    count_variable = [
                        count_var for count_var in struct.members if count_var.name == member.length][0]
                    out.append(
                        f'  for (int i = 0; i < {struct_accessor}->{count_variable.name}; i++) {{\n')
                    out.append(
                        f'    {name}->add_{member.name.lower()}({struct_accessor}->{member.name}[i]);\n')
                    out.append('  }\n')
                else:
                    log("unknown length member:",
                        struct_type, member.cDeclaration)
            elif member.pointer and member.const:
                out.append(
                    f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
            else:
                out.append(f'  // Unsupported member: {member.cDeclaration}\n')
                log("UNSUPPORTED MEMBER:", struct_type, member.cDeclaration)
        return "".join(out)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#include "remote_call.h"

#include <vulkan/vulkan.h>
#include <spdlog/spdlog.h>
#include "vvk_server.grpc.pb.h"

namespace vvk {
''')

        for cmd_name in COMMANDS_TO_GENERATE:
            command = self.vk.commands[cmd_name]
            params = [
                'grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream']
            params.extend([param.cDeclaration.strip()
                          for param in command.params])
            out.append(
                f'{command.returnType} PackAndCall{first_letter_upper(cmd_name)}({", ".join(params)}) ')
            out.append("{\n")
            out.append("  vvk::server::VvkRequest request;\n")
            out.append(f'  request.set_method("{cmd_name}");\n')

            for param in command.params:
                if param.type in ['VkAllocationCallbacks']:
                    continue
                elif param.pointer and param.const and param.type in self.vk.structs:
                    if param.length is None:
                        out.append(
                            f'  vvk::server::{param.type}* {param.name}_proto = request.mutable_{cmd_name.lower()}()->mutable_{param.name.lower()}();\n')
                        out.append(self.fill_proto_from_struct(
                            param.type, f'{param.name}_proto', f'{param.name}'))
                    else:
                        log("non zero length param:",
                            cmd_name, param.cDeclaration)
                elif param.pointer and not param.const and param.type in self.vk.handles:
                    if param.length is None:
                        out.append(
                            f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}(reinterpret_cast<uint64_t>(*{param.name}));\n')
                    else:
                        # only vkEnumerate* commands return multiple handles
                        assert ("vkEnumerate" in cmd_name)

                        out.append(f'  if ({param.name}) {{\n')
                        out.append(
                            "    // the value we set is just a sentinel value, only its presence should be checked\n")
                        out.append(
                            f'    request.mutable_{cmd_name.lower()}()->add_{param.name.lower()}(reinterpret_cast<uint64_t>({param.name}));\n')
                        out.append("  } else {\n")
                        out.append(
                            f'    request.mutable_{cmd_name.lower()}()->set_{param.length.lower()}(0);\n')
                        out.append("  }\n")
                elif param.pointer and not param.const:
                    if param.length is None:
                        out.append(
                            f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}(*{param.name});\n')
                    else:
                        log("non zero length param:",
                            cmd_name, param.cDeclaration)
                elif param.type in self.vk.handles:
                    out.append(
                        f'  request.mutable_{cmd_name.lower()}()->set_{param.name.lower()}(reinterpret_cast<uint64_t>({param.name}));\n')
                else:
                    out.append(
                        f"  // Unsupported param: {param.cDeclaration}\n")
                    log("UNSUPPORTED PARAM:", cmd_name, param.cDeclaration)

            out.append("  vvk::server::VvkResponse response;\n")

            out.append('''
  if (!stream->Write(request)) {
    spdlog::error("Failed to write request to server");
  }

  if (!stream->Read(&response)) {
    spdlog::error("Failed to read response from server");
  }
''')

            if command.returnType == "VkResult":
                out.append(
                    "  return static_cast<VkResult>(response.result());\n")

            out.append("}\n")

        out.append("}  // namespace vvk\n")

        self.write("".join(out))


class ClientHeaderGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''#include "vulkan/vulkan_core.h"

#include <grpcpp/grpcpp.h>
#include "vvk_server.pb.h"

namespace vvk {
''')

        for cmd_name in COMMANDS_TO_GENERATE:
            command = self.vk.commands[cmd_name]
            params = [
                'grpc::ClientReaderWriter<vvk::server::VvkRequest, vvk::server::VvkResponse>* stream']
            params.extend([param.cDeclaration.strip()
                          for param in command.params])
            out.append(
                f'{command.returnType} PackAndCall{first_letter_upper(cmd_name)}({", ".join(params)});\n')

        out.append("}  // namespace vvk\n")

        self.write("".join(out))


def generate_client_src():
    SetTargetApiName('vulkan')
    SetMergedApiNames('vulkan')
    opts = BaseGeneratorOptions(
        customFileName="remote_call.cpp",
        customDirectory="./commons",
    )
    gen = ClientSrcGenerator()
    reg = Registry(gen, opts)
    tree = ElementTree.parse("./Vulkan-Headers/registry/vk.xml")
    reg.loadElementTree(tree)
    reg.apiGen()


def generate_client_header():
    SetTargetApiName('vulkan')
    SetMergedApiNames('vulkan')
    opts = BaseGeneratorOptions(
        customFileName="remote_call.h",
        customDirectory="./commons",
    )
    gen = ClientHeaderGenerator()
    reg = Registry(gen, opts)
    tree = ElementTree.parse("./Vulkan-Headers/registry/vk.xml")
    reg.loadElementTree(tree)
    reg.apiGen()


def generate_client():
    generate_client_header()
    generate_client_src()
