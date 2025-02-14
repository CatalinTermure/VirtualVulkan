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
]


def first_letter_upper(name: str) -> str:
    return name[0].upper() + name[1:]


def is_output_command(generator: BaseGenerator, command: str) -> bool:
    for param in generator.vk.commands[command].params:
        if param.pointer and not param.const:
            return True
    return False
