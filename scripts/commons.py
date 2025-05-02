import copy
from base_generator import Member
from .vvk_generator import VvkGenerator
from dataclasses import dataclass
import re


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
    "vkGetPhysicalDeviceFormatProperties",
    "vkCreateDevice",
    "vkDestroyDevice",
    "vkEnumerateInstanceExtensionProperties",
    "vkEnumerateDeviceExtensionProperties",
    "vkGetPhysicalDeviceMemoryProperties",
    "vkGetPhysicalDeviceFeatures",
    "vkGetPhysicalDeviceQueueFamilyProperties",
    "vkGetDeviceQueue",
    "vkCreateFence",
    "vkDestroyFence",
    "vkCreateSemaphore",
    "vkDestroySemaphore",
    "vkAllocateMemory",
    "vkFreeMemory",
    "vkCreateImage",
    "vkDestroyImage",
    "vkBindImageMemory",
    "vkBindImageMemory2",
    "vkGetImageMemoryRequirements",
    "vkGetImageMemoryRequirements2",
    "vkCreateImageView",
    "vkDestroyImageView",
    "vkCreateCommandPool",
    "vkDestroyCommandPool",
    "vkAllocateCommandBuffers",
    "vkFreeCommandBuffers",
    "vkBeginCommandBuffer",
    "vkEndCommandBuffer",
    "vkGetImageSubresourceLayout",
    "vkCreateRenderPass",
    "vkDestroyRenderPass",
    "vkCreatePipelineLayout",
    "vkDestroyPipelineLayout",
    "vkCreateShaderModule",
    "vkDestroyShaderModule",
    "vkCreateGraphicsPipelines",
    "vkDestroyPipeline",
    "vkCreateFramebuffer",
    "vkDestroyFramebuffer",
    "vkWaitForFences",
    "vkResetFences",
    "vkResetCommandPool",
    "vkCmdBeginRenderPass",
    "vkCmdEndRenderPass",
    "vkCmdBindPipeline",
    "vkCmdSetViewport",
    "vkCmdSetScissor",
    "vkCmdDraw",
    "vkQueueSubmit",
    "vkDeviceWaitIdle",
    "vkQueueWaitIdle",
    "vkCmdPipelineBarrier",
    "vkCmdCopyImageToBuffer",
    "vkGetPhysicalDeviceProperties2",
    "vkGetPhysicalDeviceFeatures2",
]


TRIVIAL_TYPES: dict[str, TypeInfo] = {
    "uint32_t": TypeInfo(cast_to=None),
    "VkBool32": TypeInfo(cast_to=None),
    "float": TypeInfo(cast_to=None),
    "size_t": TypeInfo(cast_to=None),
    "int32_t": TypeInfo(cast_to=None),
    "uint64_t": TypeInfo(cast_to=None),
    "VkDeviceSize": TypeInfo(cast_to="uint64_t"),
    "VkSampleMask": TypeInfo(cast_to="uint32_t"),
    "uint8_t": TypeInfo(cast_to="uint32_t"),
}


def indent(text: str, spaces: int) -> str:
    lines = text.splitlines()
    return '\n'.join(' ' * spaces + line for line in lines) + '\n'


def __fill_struct_member_from_proto(generator: VvkGenerator, struct_type: str, name: str, proto_accessor: str, member: Member) -> tuple[str, str, str]:
    pre_fill_declarations = []
    out = []
    after = []
    struct = generator.vk.structs[struct_type]
    if member.name == "sType":
        out.append(f'  {name}.sType = {struct.sType};\n')
    elif member.type == 'char' and member.fixedSizeArray:
        out.append(
            f'  strncpy({name}.{member.name}, {proto_accessor}.{member.name.lower()}().c_str(), {member.length});\n')
    elif "Flags" in member.type or "FlagBits" in member.type:
        if member.length is None:
            out.append(
                f'  {name}.{member.name} = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}());\n')
        else:
            aux_var = f'{name}_{member.name}'
            index_name = f'{member.name}_indx'
            pre_fill_declarations.append(
                f'  {member.type}* {aux_var} = new {member.type}[{proto_accessor}.{member.name.lower()}_size()]();\n')
            pre_fill_declarations.append(
                f'  {name}.{member.name} = {aux_var};\n')
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {proto_accessor}.{member.name.lower()}_size(); {index_name}++)')
            out.append(' {\n')
            out.append(
                f'    {aux_var}[{index_name}] = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}({index_name}));\n')
            out.append('  }\n')
            after.append(f'  delete[] {name}.{member.name};\n')
    elif member.type in generator.vk.enums:
        if member.length is None:
            out.append(
                f'  {name}.{member.name} = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}());\n')
        else:
            assert (member.const and member.pointer)
            out.append(
                f'  {name}.{member.name} = reinterpret_cast<const {member.type}*>({proto_accessor}.{member.name.lower()}().data());\n')
    elif member.type in TRIVIAL_TYPES:
        type_info = TRIVIAL_TYPES[member.type]
        if member.fixedSizeArray:
            index_name = f'{member.name}_indx'
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {member.length}; {index_name}++) {{\n')
            if type_info.cast_to is None:
                out.append(
                    f'    {name}.{member.name}[{index_name}] = {proto_accessor}.{member.name.lower()}({index_name});\n')
            else:
                out.append(
                    f'    {name}.{member.name}[{index_name}] = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}({index_name}));\n')
            out.append('  }\n')
        elif member.length is None:
            if type_info.cast_to is None:
                out.append(
                    f'  {name}.{member.name} = {proto_accessor}.{member.name.lower()}();\n')
            else:
                out.append(
                    f'  {name}.{member.name} = static_cast<{member.type}>({proto_accessor}.{member.name.lower()}());\n')
        else:
            aux_var = f'{name}_{member.name}'
            index_name = f'{member.name}_indx'
            # we use the aux_var because the members have const qualifiers
            pre_fill_declarations.append(
                f'  {member.type}* {aux_var} = new {member.type}[{proto_accessor}.{member.name.lower()}_size()]();\n')
            pre_fill_declarations.append(
                f'  {name}.{member.name} = {aux_var};\n')
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {proto_accessor}.{member.name.lower()}_size(); {index_name}++)')
            out.append(' {\n')
            out.append(
                f'    {aux_var}[{index_name}] = {proto_accessor}.{member.name.lower()}({index_name});\n')
            out.append('  }\n')
            after.append(f'  delete[] {name}.{member.name};\n')
    elif member.pointer and member.const and member.type in generator.vk.structs:
        if member.length is None:
            aux_var = f'{name}_{member.name}'
            pre_fill_declarations.append(
                f'  {member.type} {aux_var} = {{}};\n')
            out_, after_ = fill_struct_from_proto(generator,
                                                  member.type, aux_var, f'{proto_accessor}.{member.name.lower()}()')
            out.append(out_)
            out.append(
                f'  {name}.{member.name} = &{aux_var};\n')
            if after_:
                after.append(
                    f'  const {member.type} &{aux_var} = *{name}.{member.name};\n')
                after.append(after_)
        else:
            index_name = f'{member.name}_indx'
            pre_fill_declarations.append(
                f'  {member.type}* {name}_{member.name} = new {member.type}[{proto_accessor}.{member.name.lower()}_size()]();\n')
            pre_fill_declarations.append(
                f'  {name}.{member.name} = {name}_{member.name};\n')
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {proto_accessor}.{member.name.lower()}_size(); {index_name}++)')
            out.append(' {\n')
            out.append(
                f'    {member.type} &{name}_{member.name}_i = {name}_{member.name}[{index_name}];\n')
            out_, after_ = fill_struct_from_proto(
                generator, member.type, f'{name}_{member.name}_i', f'{proto_accessor}.{member.name.lower()}({index_name})')
            out.append(indent(out_, 2))
            out.append('  }\n')
            if after_:
                after.append(
                    f'  for (int {index_name} = 0; {index_name} < {proto_accessor}.{member.name.lower()}_size(); {index_name}++)')
                after.append('  {\n')
                after.append(
                    f'    const {member.type} &{name}_{member.name}_i = {name}.{member.name}[{index_name}];\n')
                after.append(indent(after_, 2))
                after.append('  }\n')
            after.append(f'  delete[] {name}.{member.name};\n')
    elif not member.pointer and member.type in generator.vk.structs:
        if member.length is None:
            aux_var = f'{name}_{member.name}'
            pre_fill_declarations.append(
                f'  {member.type} &{aux_var} = {name}.{member.name};\n')
            out_, after_ = fill_struct_from_proto(generator, member.type,
                                                  aux_var, f'{proto_accessor}.{member.name.lower()}()')
            out.append(out_)
            if after_:
                after.append(
                    f'  const {member.type} &{aux_var} = {name}.{member.name};\n')
                after.append(after_)
        else:
            # if it's not a pointer, it must be a fixed size array
            assert (member.fixedSizeArray)
            index_name = f'{member.name}_indx'
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {proto_accessor}.{member.name.lower()}_size(); {index_name}++)')
            out.append(' {\n')
            out.append(
                f'    {member.type} &{name}_{member.name}_i = {name}.{member.name}[{index_name}];\n')
            out_, after_ = fill_struct_from_proto(
                generator, member.type, f'{name}_{member.name}_i', f'{proto_accessor}.{member.name.lower()}({index_name})')
            out.append(indent(out_, 2))
            out.append('  }\n')
            after.append(after_)
    elif member.pointer and member.type in generator.vk.handles:
        assert (member.const)
        out.append(
            f'  {name}.{member.name} = reinterpret_cast<const {member.type}*>({proto_accessor}.{member.name.lower()}().data());\n')
    elif not member.pointer and member.type in generator.vk.handles:
        out.append(
            f'  {name}.{member.name} = reinterpret_cast<{member.type}>({proto_accessor}.{member.name.lower()}());\n')
    elif 'const char* const*' in member.cDeclaration:
        aux_var = f'{name}_{member.name}'
        pre_fill_declarations.append(
            f'  const char** {aux_var} = new const char*[{proto_accessor}.{member.name.lower()}_size()]();\n')
        pre_fill_declarations.append(
            f'  {name}.{member.name} = {aux_var};\n')
        index_name = f'{member.name}_indx'
        out.append(
            f'  for (int {index_name} = 0; {index_name} < {proto_accessor}.{member.name.lower()}_size(); {index_name}++)')
        out.append(' {\n')
        out.append(
            f'    {aux_var}[{index_name}] = {proto_accessor}.{member.name.lower()}({index_name}).data();\n')
        out.append('  }\n')
        after.append(f'  delete[] {name}.{member.name};\n')
    elif member.pointer and member.const:
        out.append(
            f'  {name}.{member.name} = {proto_accessor}.{member.name.lower()}().data();\n')
    else:
        out.append(f'  // Unsupported member: {member.cDeclaration}\n')
        print("UNSUPPORTED MEMBER:", name, member.cDeclaration)
    return "".join(pre_fill_declarations), "".join(out), "".join(after)


def fill_struct_from_proto(generator: VvkGenerator, struct_type: str, name: str, proto_accessor: str) -> tuple[str, str]:
    out = []
    after = []
    struct = generator.vk.structs[struct_type]
    for member in struct.members:
        if member.optional:
            if member.name == "pNext":
                out.append(
                    f'  {name}.pNext = nullptr; // pNext chains are currently unsupported\n')
            else:
                declarations_, out_, after_ = __fill_struct_member_from_proto(
                    generator, struct_type, name, proto_accessor, member)
                out.append(declarations_)
                if member.length is None:
                    out.append(
                        f'  if ({proto_accessor}.has_{member.name.lower()}()) {{\n')
                else:
                    out.append(
                        f'  if ({proto_accessor}.{member.name.lower()}_size()) {{\n')
                out.append(
                    indent(out_, 2))
                out.append('  } else {\n')
                if member.pointer:
                    out.append(
                        f'    {name}.{member.name} = nullptr;\n')
                else:
                    out.append(
                        f'    {name}.{member.name} = {member.type}{{}};\n')
                out.append('  }\n')
                if after_:
                    # if the member is an array, then we always allocate it, even if it's empty
                    # so we always need to free it, this is not true for members that are not arrays
                    if member.length is None:
                        after.append(
                            f'  if ({proto_accessor}.has_{member.name.lower()}()) {{\n')
                        after.append(indent(after_, 2))
                        after.append('  }\n')
                    else:
                        after.append(after_)
        else:
            out1_, out2_, after_ = __fill_struct_member_from_proto(
                generator, struct_type, name, proto_accessor, member)
            out.append(out1_)
            out.append(out2_)
            after.append(after_)
    return "".join(out), "".join(after)


def access_length_member_from_struct(generator: VvkGenerator, struct_type: str, name: str, struct_accessor: str, member: Member) -> str:
    """
    Returns code necessary to access the length of a struct member.

    The length will be stored in a variable with the format f'{name}_{member.name}_length'.

    Args:
        member (Member): The member whose length is to be accessed.

    Returns:
        str: A string representing code necessary to access the length of a struct member.
    """
    struct = generator.vk.structs[struct_type] if struct_type in generator.vk.structs else None
    length = member.length
    for word in re.findall(r'\w+', member.length):
        if struct is not None and word in [m.name for m in struct.members]:
            length = str.replace(member.length, word,
                                 f'{struct_accessor}->{word}')
    return f'  const size_t {name}_{member.name}_length = {length};\n'


def __fill_proto_from_member(generator: VvkGenerator, struct_type: str, name: str, struct_accessor: str, member: Member) -> str:
    out = []
    if member.name in ['sType']:
        return ""
    elif member.name == 'pNext':
        out.append("  // pNext chains are currently not supported\n")
    elif member.type == 'char' and member.fixedSizeArray:
        out.append(
            f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
    elif member.type in TRIVIAL_TYPES:
        type_info = TRIVIAL_TYPES[member.type]
        if member.length is None:
            if type_info.cast_to is None:
                out.append(
                    f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
            else:
                out.append(
                    f'  {name}->set_{member.name.lower()}(static_cast<{type_info.cast_to}>({struct_accessor}->{member.name}));\n')
        else:
            out.append(access_length_member_from_struct(
                generator, struct_type, name, struct_accessor, member))
            index_name = f'{member.name}_indx'
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {name}_{member.name}_length; {index_name}++) {{\n')
            if type_info.cast_to is None:
                out.append(
                    f'    {name}->add_{member.name.lower()}({struct_accessor}->{member.name}[{index_name}]);\n')
            else:
                out.append(
                    f'    {name}->add_{member.name.lower()}(static_cast<{type_info.cast_to}>({struct_accessor}->{member.name}[{index_name}]));\n')
            out.append('  }\n')
    elif "Flags" in member.type or "FlagBits" in member.type:
        if member.length is None:
            out.append(
                f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
        else:
            out.append(access_length_member_from_struct(
                generator, struct_type, name, struct_accessor, member))
            index_name = f'{member.name}_indx'
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {name}_{member.name}_length; {index_name}++) {{\n')
            out.append(
                f'    {name}->add_{member.name.lower()}(static_cast<{member.type}>({struct_accessor}->{member.name}[{index_name}]));\n')
            out.append('  }\n')
    elif member.type in generator.vk.enums:
        if member.length is None:
            out.append(
                f'  {name}->set_{member.name.lower()}(static_cast<vvk::server::{member.type}>({struct_accessor}->{member.name}));\n')
        else:
            out.append(access_length_member_from_struct(
                generator, struct_type, name, struct_accessor, member))
            index_name = f'{member.name}_indx'
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {name}_{member.name}_length; {index_name}++) {{\n')
            out.append(
                f'    {name}->add_{member.name.lower()}(static_cast<vvk::server::{member.type}>({struct_accessor}->{member.name}[{index_name}]));\n')
            out.append('  }\n')
    elif member.pointer and member.const and member.type in generator.vk.structs:
        if member.length is None:
            out.append(
                f'  FillProtoFromStruct({name}->mutable_{member.name.lower()}(), {struct_accessor}->{member.name});\n')
            generator.required_functions.add(
                f'FillProtoFromStruct/{member.type}')
        else:
            out.append(access_length_member_from_struct(
                generator, struct_type, name, struct_accessor, member))
            index_name = f'{member.name}_indx'
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {name}_{member.name}_length; {index_name}++) {{\n')
            out.append(
                f'    FillProtoFromStruct({name}->add_{member.name.lower()}(), (&{struct_accessor}->{member.name}[{index_name}]));\n')
            generator.required_functions.add(
                f'FillProtoFromStruct/{member.type}')
            out.append('  }\n')
    elif not member.pointer and member.type in generator.vk.structs:
        if member.length is None:
            out.append(
                f'  FillProtoFromStruct({name}->mutable_{member.name.lower()}(), &{struct_accessor}->{member.name});\n')
            generator.required_functions.add(
                f'FillProtoFromStruct/{member.type}')
        else:
            # if it's not a pointer, it must be a fixed size array
            assert (member.fixedSizeArray)
            out.append(access_length_member_from_struct(
                generator, struct_type, name, struct_accessor, member))
            index_name = f'{member.name}_indx'
            out.append(
                f'  for (int {index_name} = 0; {index_name} < {name}_{member.name}_length; {index_name}++) {{\n')
            out.append(
                f'    FillProtoFromStruct({name}->add_{member.name.lower()}(), &{struct_accessor}->{member.name}[{index_name}]);\n')
            generator.required_functions.add(
                f'FillProtoFromStruct/{member.type}')
            out.append('  }\n')
    elif member.pointer and member.type in generator.vk.handles:
        assert (member.const)
        out.append(access_length_member_from_struct(
            generator, struct_type, name, struct_accessor, member))
        index_name = f'{member.name}_indx'
        out.append(
            f'  for (int {index_name} = 0; {index_name} < {name}_{member.name}_length; {index_name}++) {{\n')
        out.append(
            f'    {name}->add_{member.name.lower()}(reinterpret_cast<uint64_t>({struct_accessor}->{member.name}[{index_name}]));\n')
        out.append('  }\n')
    elif not member.pointer and member.type in generator.vk.handles:
        out.append(
            f'  {name}->set_{member.name.lower()}(reinterpret_cast<uint64_t>({struct_accessor}->{member.name}));\n')
    elif 'const char* const*' in member.cDeclaration:
        out.append(access_length_member_from_struct(
            generator, struct_type, name, struct_accessor, member))
        index_name = f'{member.name}_indx'
        out.append(
            f'  for (int {index_name} = 0; {index_name} < {name}_{member.name}_length; {index_name}++) {{\n')
        out.append(
            f'    {name}->add_{member.name.lower()}({struct_accessor}->{member.name}[{index_name}]);\n')
        out.append('  }\n')
    elif member.pointer and member.const:
        if member.type == 'void':
            assert (member.length is not None)
            out.append(access_length_member_from_struct(
                generator, struct_type, name, struct_accessor, member))
            out.append(
                f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name}, {name}_{member.name}_length);\n')
        else:
            out.append(
                f'  {name}->set_{member.name.lower()}({struct_accessor}->{member.name});\n')
    else:
        out.append(f'  // Unsupported member: {member.cDeclaration}\n')
        print("UNSUPPORTED MEMBER:", struct_type, member.cDeclaration)
    return "".join(out)


def fill_proto_from_struct(generator: VvkGenerator, struct_type: str, name: str, struct_accessor: str) -> str:
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


def __get_function_definition(generator: VvkGenerator, func: str) -> str:
    (func_name, type_name) = func.split('/')
    if func_name == "FillProtoFromStruct":
        out: list[str] = []
        out.append(
            f'void FillProtoFromStruct(vvk::server::{type_name}* proto, const {type_name}* original_struct) {{\n')
        out.append(fill_proto_from_struct(
            generator, type_name, 'proto', 'original_struct'))
        out.append("}\n")
        return "".join(out)
    return 'static_assert(false, "Unkown function type");\n'


def get_required_function_definitions(generator: VvkGenerator) -> list[str]:
    required_function_definitions: dict[str, str] = {}
    adding_done = False
    while not adding_done:
        adding_done = True
        old_required_functions = copy.deepcopy(generator.required_functions)
        for func in old_required_functions:
            if func not in required_function_definitions:
                adding_done = False
                required_function_definitions[func] = __get_function_definition(generator,
                                                                                func)
    return sorted(
        [value for value in required_function_definitions.values()])
