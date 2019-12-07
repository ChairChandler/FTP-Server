QT -= gui
QT += testlib

CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

TEMPLATE = subdirs

SUBDIRS += \
    integration_tests \
    src \
    unit_tests
