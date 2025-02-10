from generators.base_generator import BaseGenerator


def first_letter_upper(name: str) -> str:
    return name[0].upper() + name[1:]


def is_output_command(generator: BaseGenerator, command: str) -> bool:
    handle_types = [handle.name for handle in generator.vk.handles.values()]
    for param in generator.vk.commands[command].params:
        if param.pointer and not param.const:
            if param.type in handle_types:
                continue
            return True
    return False
