import sys
import os
import argparse

if __name__ == '__main__':
    SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
    VK_DOCS_DIR = SCRIPT_DIR + os.path.sep + \
        "Vulkan-Docs" + os.path.sep + "scripts"
    sys.path.append(VK_DOCS_DIR)

    from scripts.generator import generate
    generate()
