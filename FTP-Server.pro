QT -= gui
QT += testlib

CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

TEMPLATE = subdirs

SUBDIRS += \
    src.pro \
    test
