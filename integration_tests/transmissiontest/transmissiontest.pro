QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_transmissiontest.cpp\
            FakeTransmissionClasses.cpp

HEADERS += FakeTransmissionClasses.h

CONFIG += c++17 console

include(../unit_tests.pri)