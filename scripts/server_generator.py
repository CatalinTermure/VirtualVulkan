from xml.etree import ElementTree
from reg import Registry
from generators.base_generator import BaseGenerator, BaseGeneratorOptions, SetTargetApiName, SetMergedApiNames
from generators.vulkan_object import Param, Member
from .commons import first_letter_upper, is_output_command, COMMANDS_TO_GENERATE, RetVal
import copy

C_TYPE_TO_PROTO_TYPE = {
    "uint32_t": "uint32",
    "char*": "string",
    "char**": "repeated string",
    "VkDeviceSize": "uint64",
    "VkBool32": "bool",
    "float": "float",
    "size_t": "uint64",
    "int32_t": "int32",
    "uint8_t": "uint32",
}

required_structs: set[str] = set()


def get_proto_type(generator: BaseGenerator, param: Param | Member | RetVal) -> str:
    param_type = param.type + ("*" if param.pointer else "")
    if "const char* const*" in param.cDeclaration:
        param_type = "char**"
    if param.fixedSizeArray:
        if param.type == 'char':
            return "string"
        non_pointer_param = copy.deepcopy(param)
        non_pointer_param.fixedSizeArray = None
        return f'repeated {get_proto_type(generator, non_pointer_param)}'
    if param_type in C_TYPE_TO_PROTO_TYPE:
        return C_TYPE_TO_PROTO_TYPE[param_type]
    if param.pointer:
        non_pointer_param = copy.deepcopy(param)
        non_pointer_param.pointer = False
        return f'repeated {get_proto_type(generator, non_pointer_param)}'
    if param.type in generator.vk.handles:
        return "uint64"
    if param.type in generator.vk.structs:
        required_structs.add(param.type)
        return param.type
    if param.type in generator.vk.enums:
        required_structs.add(param.type)
        return param.type
    if param.type in generator.vk.bitmasks:
        return "uint32"
    if "Flags" in param.type:
        return "uint32"
    return "UnknownType"


def get_param_proto_declaration(generator: BaseGenerator, param: Param | Member, index: int) -> str:
    param_type = get_proto_type(generator, param)
    comment = " NON-CONST POINTER" if param.pointer and not param.const else ""
    return f"{param_type} {param.name} = {index}; // {param.cDeclaration.strip()}" + comment


class ServerSrcGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def generate(self):
        additional_messages = []
        params_types_oneof = []
        response_types_oneof = []
        out = []
        params_index = 2
        response_index = 2
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''syntax = "proto3";

package vvk.server;

import "vvk_types.proto";

service VvkServer {
  // We will use a single bidirection streaming RPC to call all the Vulkan functions
  // This is because we must guarantee that the order of the calls is the same as the order of the calls in the Vulkan API
  rpc CallMethods (stream VvkRequest) returns (stream VvkResponse) {}
}

message VvkRequest {
  string method = 1;
  oneof params {
''')
        for command in self.vk.commands.values():
            if command.name not in COMMANDS_TO_GENERATE:
                continue
            capitalized_name = first_letter_upper(command.name)
            if is_output_command(self, command.name):
                output_params: list[Param | RetVal] = []
                if command.returnType != 'void' and command.returnType != 'VkResult':
                    output_params.append(
                        RetVal(name="result",
                               type=command.returnType,
                               const=False,
                               pointer=False,
                               fixedSizeArray=[],
                               cDeclaration=f"{command.returnType} result"))
                for param in command.params:
                    if param.pointer and not param.const:
                        param_not_pointer = copy.deepcopy(param)
                        param_not_pointer.pointer = False
                        output_params.append(param_not_pointer)

                response_types_oneof.append(
                    f'    {capitalized_name}Response {command.name} = {response_index};\n')
                response_index += 1

                additional_messages.append(
                    f"message {capitalized_name}Response {{\n")
                for index, param in enumerate(output_params):
                    additional_messages.append(
                        f"  {get_param_proto_declaration(self, param, index + 1)}\n")
                additional_messages.append("}\n\n")
            else:
                pass

            params_types_oneof.append(
                f'    {capitalized_name}Params {command.name} = {params_index};\n')
            params_index += 1

            additional_messages.append(
                f"message {capitalized_name}Params {{\n")
            for index, param in enumerate(command.params):
                additional_messages.append(
                    f"  {get_param_proto_declaration(self, param, index + 1)}\n")
            additional_messages.append("}\n\n")

        out.extend(params_types_oneof)

        out.append('''  }
}

message VvkResponse {
  uint32 result = 1;
  oneof response {
''')

        out.extend(response_types_oneof)

        out.append('  }\n}\n\n')

        out.extend(additional_messages)

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
        customDirectory="./ignore",
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
