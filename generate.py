import sys
import os
import argparse

if __name__ == '__main__':
    SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
    VK_HEADERS_DIR = SCRIPT_DIR + os.path.sep + \
        "Vulkan-Headers" + os.path.sep + "registry"
    VK_UTILITY_LIBRARY_DIR = SCRIPT_DIR + os.path.sep + \
        "Vulkan-Utility-Libraries" + os.path.sep + \
        "scripts"
    sys.path.append(VK_HEADERS_DIR)
    sys.path.append(VK_UTILITY_LIBRARY_DIR)

    from scripts.generator import generate
    generate()
