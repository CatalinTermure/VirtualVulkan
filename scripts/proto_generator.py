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
        if param.length:
            return f'repeated {get_proto_type(generator, non_pointer_param)}'
        else:
            return get_proto_type(generator, non_pointer_param)
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


class ServerProtoGenerator(BaseGenerator):
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
                        if param.length:
                            output_params.append(param)
                        else:
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


class TypesProtoGenerator(BaseGenerator):
    def __init__(self):
        BaseGenerator.__init__(self)

    def generate(self):
        input_messages = []
        out = []
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''syntax = "proto3";

package vvk.server;

message VkAllocationCallbacks {
  uint64 pUserData = 1;
  uint64 pfnAllocation = 2;
  uint64 pfnReallocation = 3;
  uint64 pfnFree = 4;
  uint64 pfnInternalAllocation = 5;
  uint64 pfnInternalFree = 6;
}

''')

        for enum in self.vk.enums.values():
            out.append(f"enum {enum.name} {{\n")
            for index, value in enumerate(enum.fields):
                out.append(f"  {value.name} = {index};\n")
            out.append("}\n\n")

        manually_overridden_structs = {
            "VkAllocationCallbacks"
        }

        # TODO: make this more efficient and less duplicated
        old_required_structs = set()
        while old_required_structs != required_structs:
            old_required_structs = copy.deepcopy(required_structs)
            for struct in self.vk.structs.values():
                if struct.name not in required_structs:
                    continue
                for member in struct.members:
                    if member.name == "pNext" or member.name == "sType":
                        continue
                    _ = get_param_proto_declaration(self, member, -1)

        for struct in self.vk.structs.values():
            if struct.name not in required_structs:
                continue
            if struct.name in manually_overridden_structs:
                continue
            is_supported = True
            if not is_supported:
                out.append(f"// {struct.name} is not supported\n\n")
                continue
            out.append(f"message {struct.name} {{\n")
            index = 0
            for member in struct.members:
                if member.name == "pNext":
                    continue
                if member.name == "sType":
                    continue
                out.append(
                    f"  {get_param_proto_declaration(self, member, index + 1)}\n")
                index += 1
            out.append("}\n\n")

        out.extend(input_messages)

        self.write("".join(out))


def generate_server_proto():
    SetTargetApiName('vulkan')
    SetMergedApiNames('vulkan')
    opts = BaseGeneratorOptions(
        customFileName="vvk_server.proto",
        customDirectory="./proto",
    )
    gen = ServerProtoGenerator()
    reg = Registry(gen, opts)
    tree = ElementTree.parse("./Vulkan-Headers/registry/vk.xml")
    reg.loadElementTree(tree)
    reg.apiGen()


def generate_types_proto():
    SetTargetApiName('vulkan')
    SetMergedApiNames('vulkan')
    opts = BaseGeneratorOptions(
        customFileName="vvk_types.proto",
        customDirectory="./proto",
    )
    gen = TypesProtoGenerator()
    reg = Registry(gen, opts)
    tree = ElementTree.parse("./Vulkan-Headers/registry/vk.xml")
    reg.loadElementTree(tree)
    reg.apiGen()


def generate_proto():
    generate_server_proto()
    generate_types_proto()
