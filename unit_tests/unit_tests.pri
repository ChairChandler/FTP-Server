include(../TestIncludeFiles.pri)
include(../TestIncludePath.pri)

HEADERS += $$PWD/common/fakeaccountdatabasefactory.h \
    $$PWD/common/fakeaccountinfobuilder.h \
$$PWD/common/fakebsdsocketfactory.h

SOURCES += $$PWD/common/fakeaccountdatabasefactory.cpp \
    $$PWD/common/fakeaccountinfobuilder.cpp \
$$PWD/common/fakebsdsocketfactory.cpp

INCLUDEPATH += $$PWD/common
