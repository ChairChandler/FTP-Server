from os import path
from re import findall
from sys import argv

isMain = lambda x: x.find("main.cpp") > -1

def main(srcProPath, testIncludeFilesPriPath):
    with open(srcProPath, "r") as f:
        lines = "".join(f.readlines())
        headers = findall(r".+\.h.*", lines)
        cpp = findall(r".+\.cpp.*", lines)
        
        
        for i in cpp:
            if isMain(i):
                cpp.remove(i)

        for i, l in enumerate(headers):
            l = l.replace(' ', '')
            headers[i] = f'$$PWD/src/{l}'

        for i, l in enumerate(cpp):
            l = l.replace(' ', '')
            cpp[i] = f'$$PWD/src/{l}'

        with open(testIncludeFilesPriPath, "w+") as g:
            g.write("HEADERS += \\")
            g.write("\n")
            g.writelines("\n".join(headers))
            g.write("\n")
            g.write("SOURCES += \\")
            g.write("\n")
            g.writelines("\n".join(cpp))

if __name__ == "__main__":
    main(argv[1], argv[2])

