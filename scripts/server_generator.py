from xml.etree import ElementTree
from reg import Registry
from generators.base_generator import BaseGenerator, BaseGeneratorOptions, SetTargetApiName, SetMergedApiNames
from .commons import first_letter_upper, COMMANDS_TO_GENERATE

TRIVIAL_TYPES = [
    "uint32_t",
    "VkBool32",
]


def log(*args):
    print("server_generator:", *args)


class ServerSrcGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def fill_struct_from_proto(self, struct_type: str, name: str, proto_accessor: str) -> str:
        out = []
        struct = self.vk.structs[struct_type]
        for member in struct.members:
            if member.name == "sType":
                out.append(f'  {name}.sType = {struct.sType};\n')
            elif member.name == "pNext":
                out.append(
                    f'  {name}.pNext = nullptr; // pNext chains are currently unsupported\n')
            elif "Flags" in member.type or member.type in TRIVIAL_TYPES:
                out.append(
                    f'  {name}.{member.name} = {proto_accessor}.{member.name.lower()}();\n')
            elif member.type in self.vk.structs:
                assert (member.pointer and member.const)
                if member.length is None:
                    aux_var_name = f'{name}_{member.name}'
                    out.append(f'  {member.type} {aux_var_name};\n')
                    out.append(self.fill_struct_from_proto(
                        member.type, aux_var_name, f'{proto_accessor}.{member.name.lower()}()'))
                    out.append(
                        f'  {name}.{member.name} = &{aux_var_name};\n')
                else:
                    log("non zero length member:",
                        struct_type, member.cDeclaration)
            elif 'const char* const*' in member.cDeclaration:
                aux_var_name = f'{name}_{member.name}'
                out.append(
                    f'  std::vector<const char*> {aux_var_name};\n')
                out.append(
                    f'  for (int i = 0; i < {proto_accessor}.{member.name.lower()}_size(); i++)')
                out.append(' {\n')
                out.append(
                    f'    {aux_var_name}.push_back({proto_accessor}.{member.name.lower()}(i).data());\n')
                out.append('  }\n')
                out.append(
                    f'  {name}.{member.name} = {aux_var_name}.data();\n')
            elif member.pointer and member.const:
                out.append(
                    f'  {name}.{member.name} = {proto_accessor}.{member.name.lower()}().data();\n')
            else:
                out.append(f'  // Unsupported member: {member.cDeclaration}\n')
                log("UNSUPPORTED MEMBER:", name, member.cDeclaration)
        return "".join(out)

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
}

''')

        for cmd_name in COMMANDS_TO_GENERATE:
            after_call_code = []
            out.append(
                f'''void UnpackAndExecute{first_letter_upper(cmd_name)}(const vvk::server::VvkRequest &request,
                                      vvk::server::VvkResponse* response) ''')
            out.append("{\n")
            out.append(f'  assert(request.method() == "{cmd_name}");\n\n')
            param_accessor = f'request.{cmd_name.lower()}()'
            command = self.vk.commands[cmd_name]
            # to get the pointer params, you need the pointee type
            for param in command.params:
                if param.type in ["VkAllocationCallbacks"]:
                    continue
                elif param.const and param.pointer:
                    if param.length is None:
                        out.append(f'  {param.type} {param.name};\n')
                        out.append(self.fill_struct_from_proto(
                            param.type, param.name, f'{param_accessor}.{param.name.lower()}()'))
                    else:
                        log("non zero length param:",
                            cmd_name, param.cDeclaration)
                elif param.pointer and not param.const and param.type in self.vk.handles:
                    if param.length is None:
                        out.append(
                            f'  {param.type} client_{param.name} = reinterpret_cast<{param.type}>({param_accessor}.{param.name.lower()}());\n')
                        out.append(f'  {param.type} server_{param.name};\n')
                        after_call_code.append(
                            f'  assert(client_to_server_handles.count(reinterpret_cast<void*>(client_{param.name})) == 0);\n')
                        after_call_code.append(
                            f'  response->mutable_{cmd_name.lower()}()->set_{param.name.lower()}(reinterpret_cast<uint64_t>(server_{param.name}));\n')
                    else:
                        log("non zero length param:",
                            cmd_name, param.cDeclaration)
            # call the function
            if command.returnType == "VkResult":
                out.append(f'  VkResult result = {cmd_name}(')
            elif command.returnType == "void":
                out.append(f'  {cmd_name}(')
            actual_parameters = []
            for param in command.params:
                if param.type in ["VkAllocationCallbacks"]:
                    actual_parameters.append("nullptr")
                elif param.const and param.pointer:
                    actual_parameters.append(f'&{param.name}')
                elif param.pointer and not param.const and param.type in self.vk.handles:
                    actual_parameters.append(f'&server_{param.name}')
                elif not param.pointer and param.type in self.vk.handles:
                    actual_parameters.append(
                        f'reinterpret_cast<{param.type}>(client_to_server_handles.at(reinterpret_cast<void*>({param_accessor}.{param.name.lower()}())))')
                else:
                    log("UNHANDLED PARAM:", cmd_name, param.name)
            out.append(", ".join(actual_parameters))
            out.append(");\n")

            out.extend(after_call_code)

            # populate the response
            if command.returnType == "VkResult":
                out.append("  response->set_result(result);\n")
            elif command.returnType == "void":
                out.append("  response->set_result(VK_SUCCESS);\n")

            # for commands which output handles, populate the handle map
            for param in command.params:
                if param.pointer and not param.const and param.type in self.vk.handles:
                    out.append(
                        f'  client_to_server_handles[client_{param.name}] = server_{param.name};\n')

            out.append("}\n")

        self.write("".join(out))


class ServerHeaderGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def generate(self):
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('#include "vvk_server.pb.h"\n\n')

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
