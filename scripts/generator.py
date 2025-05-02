from xml.etree import ElementTree

from base_generator import BaseGenerator, SetMergedApiNames, SetTargetApiName
from generator import GeneratorOptions
from vkconventions import VulkanConventions
from vulkan_object import Enum, EnumField, Member, Struct, VulkanObject
from .layer_generator import generate_layer
from .client_generator import generate_client
from .proto_generator import generate_proto
from .server_generator import generate_server


class DummyGenerator(BaseGenerator):
    def __init__(self):
        self.genOpts = GeneratorOptions()
        self.genOpts.conventions = VulkanConventions()
        self.should_insert_may_alias_macro = False

    def logMsg(self, level, *args):
        pass


# TODO: this solution is awful, but the BaseGenerator does not work for video.xml
def get_video_structs_and_enums(vk_video_tree: ElementTree.ElementTree) -> VulkanObject:
    struct_elems = vk_video_tree.findall(".//types/type[@category='struct']")

    def get_elem_members(elem: ElementTree.Element) -> list[Member]:
        members = []
        dummy_gen = DummyGenerator()
        for member_elem in elem.findall("member"):
            for comment in member_elem.findall("comment"):
                member_elem.remove(comment)
            member_name = member_elem.find('name').text
            member_type = member_elem.find('type').text
            cdecl = dummy_gen.makeCParamDecl(member_elem, 0)
            full_type = cdecl.split(member_name)[0].strip()
            limit_type = member_elem.get('limittype')
            is_const = 'const' in cdecl
            length_elem = member_elem.find('altlen') or member_elem.find('len')
            if length_elem is not None:
                print("Length element found in video.xml, this is not expected")
            is_pointer = '*' in cdecl
            fixed_size_array = cdecl.split('[')[1].split(']')[
                0] if '[' in cdecl else None
            members.append(Member(name=member_name,
                                  type=member_type,
                                  fullType=full_type,
                                  noAutoValidity=True,
                                  limitType=limit_type,
                                  const=is_const,
                                  length=None,
                                  nullTerminated=False,
                                  pointer=is_pointer,
                                  fixedSizeArray=fixed_size_array,
                                  optional=False,
                                  optionalPointer=False,
                                  externSync=False,
                                  cDeclaration=cdecl
                                  ))
        return members

    structs = [Struct(name=elem.attrib['name'], aliases=[], extensions=[],
                      version=None, protect=None, members=get_elem_members(elem),
                      union=False, returnedOnly=False, sType=None, allowDuplicate=False,
                      extends=[], extendedBy=[]) for elem in struct_elems]

    def get_enum_fields(elem: ElementTree.Element) -> list[EnumField]:
        fields = []
        dummy_gen = DummyGenerator()
        for field_elem in elem.findall("enum"):
            field_name = field_elem.attrib['name']
            [value, value_str] = dummy_gen.enumToValue(
                field_elem, True, parent_for_alias_dereference=elem)
            fields.append(EnumField(name=field_name,
                                    protect=None,
                                    negative=value < 0,
                                    value=value,
                                    valueStr=value_str,
                                    extensions=[]))
        return fields

    enums_elems = vk_video_tree.findall(".//enums[@type='enum']")
    enums = [Enum(name=elem.attrib['name'], aliases=[], protect=None,
                  bitWidth=elem.get('bitwidth') or 32,
                  returnedOnly=False,
                  fields=get_enum_fields(elem),
                  extensions=[],
                  fieldExtensions=[]) for elem in enums_elems]

    vk = VulkanObject()
    vk.structs = {struct.name: struct for struct in structs}
    vk.enums = {enum.name: enum for enum in enums}
    return vk


def generate() -> None:
    SetTargetApiName('vulkan')
    SetMergedApiNames('vulkan')
    vk_tree = ElementTree.parse("./Vulkan-Headers/registry/vk.xml")
    vk_video_tree = ElementTree.parse("./Vulkan-Headers/registry/video.xml")
    base_vk = get_video_structs_and_enums(vk_video_tree)
    vk_tree.getroot().append(vk_video_tree.getroot())

    generate_proto(vk_tree, base_vk)
    generate_server(vk_tree, base_vk)
    generate_client(vk_tree, base_vk)
    generate_layer(vk_tree, base_vk)
