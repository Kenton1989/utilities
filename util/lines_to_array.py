"""
Name: lines_to_array
========================
Function:
Reading lines from STDIN.
Add double quote(") at both side.
Add comma(,) between each line.
Print processed lines to STDOUT.
----------------
It can be used to generate string array for VS Code snippet JSON file.
"""

if __name__ == "__main__":
    while True:
        try:
            line = input()
            print('"'+line+'",')
        except EOFError:
            break