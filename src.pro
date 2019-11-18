# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = src

HEADERS = \
   src/cmds/cmdport.h \
   src/cmds/cmdquit.h \
   src/cmds/cmdstru.h \
   src/cmds/cmduser.h \
   src/accountdatabase.h \
   src/filestructure.h \
   src/ftpcommand.h \
   src/ReplyCodes.h \
   src/cmds/cmdtype.h \
   src/cmds/cmdmode.h \
   src/mode.h \
   src/transmission/transmission.h \
   src/transmission/types/asciitransmission.h \
   src/transmission/types/binarytransmission.h

SOURCES = \
   src/cmds/cmdport.cpp \
   src/cmds/cmdquit.cpp \
   src/cmds/cmdstru.cpp \
   src/cmds/cmduser.cpp \
   src/accountdatabase.cpp \
   src/ftpcommand.cpp \
   src/main.cpp \
   src/cmds/cmdtype.cpp \
   src/cmds/cmdmode.cpp \
   src/transmission/transmission.cpp \
   src/transmission/types/asciitransmission.cpp \
   src/transmission/types/binarytransmission.cpp
INCLUDEPATH = \
    src \
    src/cmds

DISTFILES +=

STATECHARTS +=
