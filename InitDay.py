import sys
import os
import subprocess

def main():
    if len(sys.argv) != 2 or not sys.argv[1].isdigit():
        print("Usage : python InitDay.py <day_number>")
        return

    n = sys.argv[1]
    files = [
        ("inc\\DayXX.h.txt", f"inc\\Day{n}.h"),
        ("src\\DayXX.cpp.txt", f"src\\Day{n}.cpp"),
    ]

    for src, dst in files:
        if not os.path.exists(src):
            print(f"Source file not found: {src}")
            continue
        with open(src, "r", encoding="utf-8") as f:
            content = f.read()
        content = content.replace("XX", n)
        with open(dst, "w", encoding="utf-8") as f:
            f.write(content)
        print(f"Generated files: {dst}")

    p = subprocess.Popen('powershell.exe -ExecutionPolicy RemoteSigned -file "makeProj.ps1"', stdout=subprocess.PIPE)
    p.communicate()

if __name__ == "__main__":
    main()