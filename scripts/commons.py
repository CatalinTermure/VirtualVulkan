from generators.base_generator import BaseGenerator, Member
from dataclasses import dataclass


@dataclass
class RetVal:
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


@dataclass
class TypeInfo:
    cast_to: str | None


COMMANDS_TO_GENERATE = [
    "vkCreateInstance",
    "vkDestroyInstance",
    "vkEnumeratePhysicalDevices",
    "vkGetPhysicalDeviceProperties",
    "vkCreateDevice",
    "vkDestroyDevice",
]


TRIVIAL_TYPES: dict[str, TypeInfo] = {
    "uint32_t": TypeInfo(cast_to=None),
    "VkBool32": TypeInfo(cast_to=None),
    "float": TypeInfo(cast_to=None),
    "size_t": TypeInfo(cast_to=None),
    "int32_t": TypeInfo(cast_to=None),
    "VkDeviceSize": TypeInfo(cast_to="uint64_t"),
    "uint8_t": TypeInfo(cast_to="uint32_t"),
}


def indent(text: str, spaces: int) -> str:
    lines = text.splitlines()
    return '\n'.join(' ' * spaces + line for line in lines) + '\n'


def __fill_struct_member_from_proto(generator: BaseGenerator, struct_type: str, name: str, proto_accessor: str, member: Member) -> tuple[str, str]:
    pre_fill_declarations = []
    out = []
    struct = generator.vk.structs[struct_type]
    if member.name == "sType":
        out.append(f'  {name}.sType = {struct.sType};\n')
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
        type_info = TRIVIAL_TYPES[member.type]
        if member.fixedSizeArray:
            out.append(
                f'  for (int i = 0; i < {member.length}; i++) {{\n')
            if type_info.cast_to is None:
                out.append(
                    f'    {name}.{member.name}[i] = {proto_accessor}.{member.name.lower()}(i);\n')
            else:
                out.append(
                    f'    {name}.{member.name}[i] = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}(i));\n')
            out.append('  }\n')
        elif member.length is None:
            if type_info.cast_to is None:
                out.append(
                    f'  {name}.{member.name} = {proto_accessor}.{member.name.lower()}();\n')
            else:
                out.append(
                    f'  {name}.{member.name} = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}());\n')
        else:
            if member.length in [member.name for member in struct.members]:
                count_variable = [
                    count_var for count_var in struct.members if count_var.name == member.length][0]
                aux_var = f'{name}_{member.name}'
                pre_fill_declarations.append(
                    f'  std::vector<{member.type}> {aux_var}({proto_accessor}.{count_variable.name.lower()}());\n')
                out.append(
                    f'  for (int i = 0; i < {proto_accessor}.{count_variable.name.lower()}(); i++)')
                out.append(' {\n')
                out.append(
                    f'    {aux_var}[i] = {proto_accessor}.{member.name.lower()}(i);\n')
                out.append('  }\n')
                out.append(
                    f'  {name}.{member.name} = {aux_var}.data();\n')
            else:
                print("unknown length member:",
                      struct_type, member.cDeclaration)
    elif member.pointer and member.const and member.type in generator.vk.structs:
        if member.length is None:
            aux_var_name = f'{name}_{member.name}'
            pre_fill_declarations.append(
                f'  {member.type} {aux_var_name} = {{}};\n')
            out.append(fill_struct_from_proto(generator,
                                              member.type, aux_var_name, f'{proto_accessor}.{member.name.lower()}()'))
            out.append(
                f'  {name}.{member.name} = &{aux_var_name};\n')
        else:
            if member.length in [member.name for member in struct.members]:
                count_variable = [
                    count_var for count_var in struct.members if count_var.name == member.length][0]
                pre_fill_declarations.append(
                    f'  std::vector<{member.type}> {name}_{member.name}({proto_accessor}.{count_variable.name.lower()}());\n')
                out.append(
                    f'  {name}.{member.name} = {name}_{member.name}.data();\n')
                out.append(
                    f'  for (int i = 0; i < {proto_accessor}.{count_variable.name.lower()}(); i++)')
                out.append(' {\n')
                out.append(
                    f'    {member.type} &{name}_{member.name}_i = {name}_{member.name}[i];\n')
                out.append(indent(fill_struct_from_proto(
                    generator, member.type, f'{name}_{member.name}_i', f'{proto_accessor}.{member.name.lower()}(i)'), 2))
                out.append('  }\n')
            else:
                print("unknown length member:",
                      struct_type, member.cDeclaration)
    elif not member.pointer and member.type in generator.vk.structs:
        out.append(fill_struct_from_proto(generator, member.type,
                                          f'{name}.{member.name}', f'{proto_accessor}.{member.name.lower()}()'))
    elif 'const char* const*' in member.cDeclaration:
        aux_var_name = f'{name}_{member.name}'
        pre_fill_declarations.append(
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
    return "".join(pre_fill_declarations), "".join(out)


def fill_struct_from_proto(generator: BaseGenerator, struct_type: str, name: str, proto_accessor: str) -> str:
    out = []
    struct = generator.vk.structs[struct_type]
    for member in struct.members:
        if member.optional:
            if member.name == "pNext":
                out.append(
                    f'  {name}.pNext = nullptr; // pNext chains are currently unsupported\n')
            else:
                declarations_, out_ = __fill_struct_member_from_proto(
                    generator, struct_type, name, proto_accessor, member)
                out.append(declarations_)
                out.append(
                    f'  if ({proto_accessor}.has_{member.name.lower()}()) {{\n')
                out.append(
                    indent(out_, 2))
                out.append('  }\n')
        else:
            out1_, out2_ = __fill_struct_member_from_proto(
                generator, struct_type, name, proto_accessor, member)
            out.append(out1_)
            out.append(out2_)
    return "".join(out)


def __fill_proto_from_member(generator: BaseGenerator, struct_type: str, name: str, struct_accessor: str, member: Member) -> str:
    out = []
    struct = generator.vk.structs[struct_type]
    if member.name in ['sType']:
        return ""
    elif member.name == 'pNext':
        out.append("  // pNext chains are currently not supported\n")
    elif member.type == 'char' and member.fixedSizeArray:
        out.append(
            f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
    elif member.type in TRIVIAL_TYPES:
        type_info = TRIVIAL_TYPES[member.type]
        if member.fixedSizeArray:
            out.append(
                f'  for (int i = 0; i < {member.length}; i++) {{\n')
            if type_info.cast_to is None:
                out.append(
                    f'    {name}->add_{member.name.lower()}({struct_accessor}->{member.name}[i]);\n')
            else:
                out.append(
                    f'    {name}->add_{member.name.lower()}(static_cast<{type_info.cast_to}>({struct_accessor}->{member.name}[i]));\n')
            out.append('  }\n')
        elif member.length is None:
            if type_info.cast_to is None:
                out.append(
                    f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
            else:
                out.append(
                    f'  {name}->set_{member.name.lower()}(static_cast<{type_info.cast_to}>({struct_accessor}->{member.name}));\n')
        else:
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
            if member.length in [member.name for member in struct.members]:
                count_variable = [
                    count_var for count_var in struct.members if count_var.name == member.length][0]
                out.append(
                    f'  for (int i = 0; i < {struct_accessor}->{count_variable.name}; i++) {{\n')
                out.append(
                    f'    vvk::server::{member.type}* {name}_{member.name}_proto = {name}->add_{member.name.lower()}();\n')
                out.append(indent(fill_proto_from_struct(generator,
                                                         member.type, f'{name}_{member.name}_proto', f'(&{struct_accessor}->{member.name}[i])'), 2))
                out.append('  }\n')
            else:
                print("unknown length member:",
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


def fill_proto_from_struct(generator: BaseGenerator, struct_type: str, name: str, struct_accessor: str) -> str:
    out = []
    struct = generator.vk.structs[struct_type]
    for member in struct.members:
        if member.optional:
            out.append(f'  if ({struct_accessor}->{member.name}) {{\n')
            out.append(
                indent(__fill_proto_from_member(generator, struct_type, name, struct_accessor, member), 2))
            out.append('  }\n')
        else:
            out.append(__fill_proto_from_member(
                generator, struct_type, name, struct_accessor, member))
    return "".join(out)


def first_letter_upper(name: str) -> str:
    return name[0].upper() + name[1:]


def is_output_command(generator: BaseGenerator, command: str) -> bool:
    for param in generator.vk.commands[command].params:
        if param.pointer and not param.const:
            return True
    return False
