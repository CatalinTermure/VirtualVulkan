from base_generator import BaseGenerator
from vulkan_object import VulkanObject


class VvkGenerator(BaseGenerator):
    def __init__(self, base_vk: VulkanObject):
        BaseGenerator.__init__(self)
        self.vk = base_vk
