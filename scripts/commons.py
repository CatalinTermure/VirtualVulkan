from generators.base_generator import BaseGenerator
from dataclasses import dataclass


@dataclass
class RetVal:
    """<command/param>"""
    name: str
    type: str  # ex) void, VkFormat, etc

    const: bool           # type contains 'const'
    # type contains a pointer (include 'PFN' function pointers)
    pointer: bool
    fixedSizeArray: list[str]  # for VkTransformMatrixKHR:matrix this is [3, 4]

    # C string of member, example:
    #   - const void* pNext
    #   - VkFormat format
    #   - VkStructureType sType
    cDeclaration: str


COMMANDS_TO_GENERATE = [
    "vkCreateInstance",
    "vkDestroyInstance",
    "vkEnumeratePhysicalDevices",
    "vkGetPhysicalDeviceProperties",
]

TRIVIAL_TYPES = [
    "uint32_t",
    "VkBool32",
    "float",
    "size_t",
    "int32_t",
]

TYPES_TO_CAST = {
    "VkDeviceSize": "uint64_t",
    "uint8_t": "uint32_t",
}


def fill_struct_from_proto(generator: BaseGenerator, struct_type: str, name: str, proto_accessor: str) -> str:
    out = []
    struct = generator.vk.structs[struct_type]
    for member in struct.members:
        if member.name == "sType":
            out.append(f'  {name}.sType = {struct.sType};\n')
        elif member.name == "pNext":
            out.append(
                f'  {name}.pNext = nullptr; // pNext chains are currently unsupported\n')
        elif member.type == 'char' and member.fixedSizeArray:
            out.append(
                f'  strncpy({name}.{member.name}, {proto_accessor}.{member.name.lower()}().c_str(), {member.length});\n')
        elif "Flags" in member.type:
            out.append(
                f'  {name}.{member.name} = {proto_accessor}.{member.name.lower()}();\n')
        elif member.type in generator.vk.enums:
            out.append(
                f'  {name}.{member.name} = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}());\n')
        elif member.type in TRIVIAL_TYPES:
            if member.fixedSizeArray:
                out.append(
                    f'  for (int i = 0; i < {member.length}; i++) {{\n')
                out.append(
                    f'    {name}.{member.name}[i] = {proto_accessor}.{member.name.lower()}(i);\n')
                out.append('  }\n')
            else:
                out.append(
                    f'  {name}.{member.name} = {proto_accessor}.{member.name.lower()}();\n')
        elif member.type in TYPES_TO_CAST:
            if member.fixedSizeArray:
                out.append(
                    f'  for (int i = 0; i < {member.length}; i++) {{\n')
                out.append(
                    f'    {name}.{member.name}[i] = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}(i));\n')
                out.append('  }\n')
            else:
                out.append(
                    f'  {name}.{member.name} = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}());\n')
        elif member.pointer and member.const and member.type in generator.vk.structs:
            if member.length is None:
                aux_var_name = f'{name}_{member.name}'
                out.append(f'  {member.type} {aux_var_name};\n')
                out.append(fill_struct_from_proto(generator,
                                                  member.type, aux_var_name, f'{proto_accessor}.{member.name.lower()}()'))
                out.append(
                    f'  {name}.{member.name} = &{aux_var_name};\n')
            else:
                print("non zero length member:",
                      struct_type, member.cDeclaration)
        elif not member.pointer and member.type in generator.vk.structs:
            out.append(fill_struct_from_proto(generator, member.type,
                                              f'{name}.{member.name}', f'{proto_accessor}.{member.name.lower()}()'))
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
            print("UNSUPPORTED MEMBER:", name, member.cDeclaration)
    return "".join(out)


def fill_proto_from_struct(generator: BaseGenerator, struct_type: str, name: str, struct_accessor: str) -> str:
    out = []
    struct = generator.vk.structs[struct_type]
    for member in struct.members:
        if member.name in ['sType']:
            continue
        elif member.name == 'pNext':
            out.append("  // pNext chains are currently not supported\n")
        elif member.type == 'char' and member.fixedSizeArray:
            out.append(
                f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
        elif member.type in TRIVIAL_TYPES:
            if member.fixedSizeArray:
                out.append(
                    f'  for (int i = 0; i < {member.length}; i++) {{\n')
                out.append(
                    f'    {name}->add_{member.name.lower()}({struct_accessor}->{member.name}[i]);\n')
                out.append('  }\n')
            else:
                out.append(
                    f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
        elif member.type in TYPES_TO_CAST:
            if member.fixedSizeArray:
                out.append(
                    f'  for (int i = 0; i < {member.length}; i++) {{\n')
                out.append(
                    f'    {name}->add_{member.name.lower()}(static_cast<{TYPES_TO_CAST[member.type]}>({struct_accessor}->{member.name}[i]));\n')
                out.append('  }\n')
            else:
                out.append(
                    f'  {name}->set_{member.name.lower()}(static_cast<{TYPES_TO_CAST[member.type]}>({struct_accessor}->{member.name}));\n')
        elif "Flags" in member.type:
            out.append(
                f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
        elif member.type in generator.vk.enums:
            out.append(
                f'  {name}->set_{member.name.lower()}(static_cast<vvk::server::{member.type}>({struct_accessor}->{member.name}));\n')
        elif member.pointer and member.const and member.type in generator.vk.structs:
            if member.length is None:
                out.append(
                    f'  vvk::server::{member.type}* {name}_{member.name}_proto = {name}->mutable_{member.name.lower()}();\n')
                out.append(fill_proto_from_struct(generator,
                                                  member.type, f'{name}_{member.name}_proto', f'{struct_accessor}->{member.name}'))
            else:
                print("non zero length member:",
                      struct_type, member.cDeclaration)
        elif not member.pointer and member.type in generator.vk.structs:
            out.append(
                f'  vvk::server::{member.type}* {name}_{member.name}_proto = {name}->mutable_{member.name.lower()}();\n')
            out.append(fill_proto_from_struct(generator,
                                              member.type, f'{name}_{member.name}_proto', f'(&{struct_accessor}->{member.name})'))
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
                print("unknown length member:",
                      struct_type, member.cDeclaration)
        elif member.pointer and member.const:
            out.append(
                f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
        else:
            out.append(f'  // Unsupported member: {member.cDeclaration}\n')
            print("UNSUPPORTED MEMBER:", struct_type, member.cDeclaration)
    return "".join(out)


def first_letter_upper(name: str) -> str:
    return name[0].upper() + name[1:]


def is_output_command(generator: BaseGenerator, command: str) -> bool:
    for param in generator.vk.commands[command].params:
        if param.pointer and not param.const:
            return True
    return False
