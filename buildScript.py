from os import path
from re import findall

isMain = lambda x: x.find("main.cpp") > -1

with open(f"{path.dirname(__file__)}/src.pro", "r") as f:
    lines = "".join(f.readlines())
    headers = findall(r".+\.h.*", lines)
    cpp = findall(r".+\.cpp.*", lines)
    
    
    for i in cpp:
        if isMain(i):
            cpp.remove(i)

    with open(f"{path.dirname(__file__)}/TestIncludeFiles.pri", "w+") as g:
        g.write("HEADERS += \\")
        g.write("\n")
        g.writelines("\n".join(headers))
        g.write("\n")
        g.write("SOURCES += \\")
        g.write("\n")
        g.writelines("\n".join(cpp))
