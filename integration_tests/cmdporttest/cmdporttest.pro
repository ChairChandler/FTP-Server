QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_cmdporttest.cpp \
    fakeclientdataserver.cpp
CONFIG += c++17 console

include(../integration_tests.pri)

HEADERS += \
    fakeclientdataserver.h
