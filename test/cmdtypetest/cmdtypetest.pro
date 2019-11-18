QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_cmdtypetest.cpp \
    FakeTransmissionClasses.cpp
CONFIG += c++17 console
include(../../TestIncludeFiles.pri)
include(../../TestIncludePath.pri)

HEADERS += \
    FakeTransmissionClasses.h
