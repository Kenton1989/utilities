"""
Name: generate_menu
========================
Function:
scan dir of this project and build a file system tree with MarkDown syntex.
The resulting tree is printed to STDOUT.

During building the tree:
non-dir file in cwd is ignored.
*/min/* is ignored.
.exe files are ignored.
hidden files (file name starts with ".") is ignored.
"""

import os
import sys

def ignore(fileName):
    return (fileName.startswith('.') or
            fileName == 'min' or
            fileName.lower().endswith('.exe'))

def generate_menu(fileName, parentDir, level = 0):
    if ignore(fileName):
        return

    fullPath = parentDir+ '/' + fileName

    print('  '*level + '- [' + fileName + '](' + fullPath + '): ')
    
    if os.path.isdir(fullPath):
        for filePath in os.listdir(fullPath):
            generate_menu(filePath, fullPath, level+1)


if __name__ == "__main__":
    for filePath in os.listdir(os.getcwd()):
        if not os.path.isdir(filePath):
            continue
        generate_menu(filePath, '.')

    

