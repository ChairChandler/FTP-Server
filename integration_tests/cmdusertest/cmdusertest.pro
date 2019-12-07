QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app
CONFIG += c++17 console

SOURCES +=  tst_cmdusertest.cpp
include(../integration_tests.pri)
