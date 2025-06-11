from xml.etree import ElementTree
from reg import Registry
from base_generator import BaseGeneratorOptions
from .vvk_generator import VvkGenerator
from vulkan_object import Param, Member, VulkanObject
from .commons import first_letter_upper, COMMANDS_TO_GENERATE, RetVal, is_struct_allowed
import copy
import inflection


C_TYPE_TO_PROTO_TYPE = {
    "uint32_t": "uint32",
    "uint64_t": "uint64",
    'int64_t': "int64",
    "char*": "bytes",
    "char**": "repeated bytes",
    "VkDeviceSize": "uint64",
    "VkBool32": "bool",
    "float": "float",
    "size_t": "uint64",
    "int32_t": "int32",
    "uint8_t": "uint32",
    'uint16_t': "uint32",
    'int': 'int32',
    "void*": "bytes",
    "void**": "uint64",
    "VkSampleMask": "uint32",

    "HANDLE": "uint64",
    "DWORD": "uint32",
    "LPCWSTR": "bytes",
    # TODO: if this ever is needed, we need to add a new proto type
    "SECURITY_ATTRIBUTES*": "uint64",

    "AHardwareBuffer*": "uint64",

    "MTLBuffer_id": "uint64",
    "MTLTexture_id": "uint64",
    "IOSurfaceRef": "uint64",
    "MTLSharedEvent_id": "uint64",

    "zx_handle_t": "uint64",

    "_screen_buffer*": "uint64",
}

required_structs: set[str] = set()


def get_proto_type(generator: VvkGenerator, param: Param | Member | RetVal) -> str:
    param_type = param.type
    if param.name.startswith("pp"):
        param_type += "**"
    elif param.pointer:
        param_type += "*"
    if param_type.startswith("PFN_"):
        return "uint64"
    if "const char* const*" in param.cDeclaration:
        param_type = "char**"
    if param.fixedSizeArray:
        if param.type == 'char':
            return "bytes"
        non_pointer_param = copy.deepcopy(param)
        non_pointer_param.fixedSizeArray = []
        return f'repeated {get_proto_type(generator, non_pointer_param)}'
    if param_type in C_TYPE_TO_PROTO_TYPE:
        return C_TYPE_TO_PROTO_TYPE[param_type]
    if param.pointer:
        non_pointer_param = copy.deepcopy(param)
        non_pointer_param.pointer = False
        if isinstance(param, RetVal):
            raise ValueError(
                f"RetVal {param.name} should not have a pointer, but it does.")
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


def get_param_proto_declaration(generator: VvkGenerator, param: Param | Member | RetVal, index: int) -> str:
    param_type = get_proto_type(generator, param)
    comment = " NON-CONST POINTER" if param.pointer and not param.const else ""
    if param.optional and "repeated" not in param_type:
        param_type = "optional " + param_type
    return f"{param_type} {param.name} = {index}; // {param.cDeclaration.strip()}" + comment


class ServerProtoGenerator(VvkGenerator):
    def __init__(self, base_vk: VulkanObject):
        VvkGenerator.__init__(self, base_vk)

    def get_output_params(self, command_name: str) -> list[Param | RetVal]:
        output_params: list[Param | RetVal] = []
        command = self.vk.commands[command_name]
        if command.returnType != 'void':
            output_params.append(
                RetVal(name="result",
                       type=command.returnType,
                       const=False,
                       pointer=False,
                       optional=False,
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
        return output_params

    def generate(self):
        additional_messages = []
        params_types_oneof = []
        response_types_oneof = []
        out = []
        params_index = 4
        response_index = 2
        out.append("// GENERATED FILE - DO NOT EDIT\n")
        out.append("// clang-format off\n")
        out.append('''syntax = "proto3";

package vvk.server;

import "vvk_types.proto";
import "vvk_presentation.proto";
import "vvk_write_memory.proto";
import "google/protobuf/empty.proto";

service VvkServer {
  // We will use a single bidirection streaming RPC to call all the Vulkan functions
  // This is because we must guarantee that the order of the calls is the same as the order of the calls in the Vulkan API
  rpc CallMethods (stream VvkRequest) returns (stream VvkResponse) {}

  rpc GetFrameStreamingCapabilities (VvkGetFrameStreamingCapabilitiesRequest) returns (StreamingCapabilities) {}
  rpc RequestFrame (VvkGetFrameRequest) returns (stream VvkGetFrameResponse) {}
  rpc WriteMappedMemory (VvkWriteMappedMemoryRequest) returns (google.protobuf.Empty) {}
}

message VvkRequest {
  string method = 1;
  oneof params {
    VvkSetupPresentationRequest setupPresentation = 2;
    VvkSetupFrameRequest setupFrame = 3;
''')
        for command in self.vk.commands.values():
            if command.name not in COMMANDS_TO_GENERATE:
                continue
            capitalized_name = first_letter_upper(command.name)
            output_params = self.get_output_params(command.name)
            if len(output_params) > 0:
                response_types_oneof.append(
                    f'    {capitalized_name}Response {command.name} = {response_index};\n')
                response_index += 1

                additional_messages.append(
                    f"message {capitalized_name}Response {{\n")
                for index, param in enumerate(output_params):
                    additional_messages.append(
                        f"  {get_param_proto_declaration(self, param, index + 1)}\n")
                additional_messages.append("}\n\n")

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
  oneof response {
    VvkSetupPresentationResponse setupPresentation = 1;
''')

        out.extend(response_types_oneof)

        out.append('  }\n}\n\n')

        out.extend(additional_messages)

        self.write("".join(out))


class TypesProtoGenerator(VvkGenerator):
    def __init__(self, base_vk: VulkanObject):
        VvkGenerator.__init__(self, base_vk)

    def generate(self):
        pnext_chain_elements = []
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

        tree: ElementTree.ElementTree = self.registry.tree

        for enum in self.vk.enums.values():
            field_definitions: list[tuple[int, str]] = []
            out.append(f"enum {enum.name} {{\n")
            enum_values: set[int] = set()
            does_alias = False
            for field in enum.fields:
                elem = tree.find(f".//enum[@name='{field.name}']")
                enum_elem = tree.find(f".//enums[@name='{enum.name}']")
                enum_value = self.enumToValue(
                    elem, True, parent_for_alias_dereference=enum_elem)[0]
                field_definitions.append(
                    (enum_value, f"  {field.name} = {enum_value};\n"))
                if enum_value in enum_values:
                    does_alias = True
                enum_values.add(enum_value)
            if does_alias:
                out.append("  option allow_alias = true;\n")
            if 0 not in enum_values:
                out.append(
                    f"  {inflection.underscore(enum.name).upper()}_UNKNOWN = 0;  // This is not part of the Vulkan spec, but proto3 enums must start with 0\n")
            elif field_definitions[0][0] != 0:
                # swap the first element with the element that has value 0 so that the first element is the one with value 0
                for i, (value, _) in enumerate(field_definitions):
                    if value == 0:
                        field_definitions[0], field_definitions[i] = field_definitions[i], field_definitions[0]
                        break
            out.extend([definition for (_, definition)
                       in field_definitions])
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
                if struct.extendedBy:
                    for extended_by in struct.extendedBy:
                        struct_extended_by = self.vk.structs[extended_by]
                        if is_struct_allowed(struct_extended_by):
                            required_structs.add(extended_by)
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
            index = 1
            for member in struct.members:
                if member.name == "sType":
                    continue
                if member.name == "pNext":
                    if struct.extendedBy:
                        pnext_chain: list[str] = []
                        pnext_chain_index = 1
                        pnext_chain.append(
                            f'message PNextChain_{struct.name} {{\n')
                        pnext_chain.append('  oneof chain_element {\n')
                        for extended_by in struct.extendedBy:
                            if extended_by not in required_structs:
                                continue
                            pnext_chain.append(
                                f'    {extended_by} {extended_by}_chain_elem = {pnext_chain_index};\n')
                            pnext_chain_index += 1
                        pnext_chain.append('  }\n')
                        pnext_chain.append('}\n')

                        if pnext_chain_index == 1:
                            continue

                        pnext_chain_elements.extend(pnext_chain)
                        out.append(
                            f'  repeated PNextChain_{struct.name} pNext = {index};\n')
                        index += 1
                else:
                    out.append(
                        f"  {get_param_proto_declaration(self, member, index)}\n")
                    index += 1
            out.append("}\n\n")

        out.extend(pnext_chain_elements)

        self.write("".join(out))


def generate_server_proto(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    opts = BaseGeneratorOptions(
        customFileName="vvk_server.proto",
        customDirectory="./proto",
    )
    gen = ServerProtoGenerator(base_vk)
    reg = Registry(gen, opts)
    reg.loadElementTree(vk_tree)
    reg.apiGen()


def generate_types_proto(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    opts = BaseGeneratorOptions(
        customFileName="vvk_types.proto",
        customDirectory="./proto",
    )
    gen = TypesProtoGenerator(base_vk)
    reg = Registry(gen, opts)
    reg.loadElementTree(vk_tree)
    reg.apiGen()


def generate_proto(vk_tree: ElementTree.ElementTree, base_vk: VulkanObject):
    generate_server_proto(vk_tree, base_vk)
    generate_types_proto(vk_tree, base_vk)
