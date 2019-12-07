# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = src

HEADERS = \
   accountinfo.h \
   bsdsocketfactory.h \
   cmds/cmdnoop.h \
   cmds/cmdport.h \
   cmds/cmdpwd.h \
   cmds/cmdquit.h \
   cmds/cmdstru.h \
   cmds/cmduser.h \
   accountdatabase.h \
   controller/ftpconnectionworker.h \
   controller/messagecommandparser.h \
   ftpfilesystem/ftpfilesystem.h \
   mode/types/streammode.h \
   structure/structure.h \
   structure/types/filestructure.h \
   ftpcommand.h \
   cmds/cmdtype.h \
   cmds/cmdmode.h \
   mode/mode.h \
   transmission/transmission.h \
   transmission/types/asciitransmission.h \
   transmission/types/binarytransmission.h \
   controller/ftpcontroller.h \
   controller/replycodes.h
    
SOURCES = \
   accountinfo.cpp \
   bsdsocketfactory.cpp \
   cmds/cmdport.cpp \
   cmds/cmdpwd.cpp \
   cmds/cmdquit.cpp \
   cmds/cmdstru.cpp \
   cmds/cmduser.cpp \
   accountdatabase.cpp \
   controller/ftpconnectionworker.cpp \
   controller/messagecommandparser.cpp \
   controller/replycodes.cpp \
   ftpfilesystem/ftpfilesystem.cpp \
   mode/types/streammode.cpp \
   structure/types/filestructure.cpp \
   ftpcommand.cpp \
   main.cpp \
   cmds/cmdtype.cpp \
   cmds/cmdmode.cpp \
   transmission/transmission.cpp \
   transmission/types/asciitransmission.cpp \
   transmission/types/binarytransmission.cpp \
   controller/ftpcontroller.cpp
INCLUDEPATH += $$PWD

DISTFILES +=

STATECHARTS +=

CONFIG += c++17
