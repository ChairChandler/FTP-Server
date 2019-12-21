# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = src

QT += widgets

HEADERS = \
   account/accountinfo.h \
   bsdsocket/bsdsocketfactory.h \
   controller/services/srv/cwdservice.h \
   controller/services/srv/listservice.h \
   controller/services/srv/mkdservice.h \
   controller/services/srv/portservice.h \
   controller/services/srv/pwdservice.h \
   controller/services/srv/retrservice.h \
   controller/services/srv/rmdservice.h \
   controller/services/srv/storservice.h \
   controller/services/srv/typeservice.h \
   controller/xmloutput/xmlcout.h \
   controller/xmloutput/xmlexception.h \
   controller/xmloutput/xmllogs.h \
   controller/xmloutput/xmlmessage.h \
   exception/namedexception.h \
   ftpcommand/cmds/cdupcmd.h \
   account/accountdatabase.h \
   controller/services/FTPservice.h \
   controller/ftpconnectionworker.h \
   ftpcommand/cmds/cwdcmd.h \
   ftpcommand/cmds/listcmd.h \
   ftpcommand/cmds/mkdcmd.h \
   ftpcommand/cmds/portcmd.h \
   ftpcommand/cmds/pwdcmd.h \
   ftpcommand/cmds/retrcmd.h \
   ftpcommand/cmds/rmdcmd.h \
   ftpcommand/cmds/storcmd.h \
   ftpcommand/cmds/typecmd.h \
   ftpcommand/commandparser.h \
   ftpcommand/parsers/cdupparser.h \
   controller/services/srv/cdupservice.h \
   ftpcommand/parsers/cwdparser.h \
   ftpcommand/parsers/listparser.h \
   ftpcommand/parsers/mkdparser.h \
   ftpcommand/parsers/portparser.h \
   ftpcommand/parsers/pwdparser.h \
   ftpcommand/parsers/retrparser.h \
   ftpcommand/parsers/rmdparser.h \
   ftpcommand/parsers/storparser.h \
   ftpcommand/parsers/typeparser.h \
   ftpfilesystem/filelocker.h \
   ftpfilesystem/ftpfilesystem.h \
   ftpcommand/ftpcommand.h \
   transmission/filetransmission.h \
   controller/ftpcontroller.h \
   controller/replycodes/replycodes.h \
   transmission/types/asciifiletransmission.h \
   transmission/types/binaryfiletransmission.h
    
SOURCES = \
   account/accountinfo.cpp \
   bsdsocket/bsdsocketfactory.cpp \
   controller/services/FTPservice.cpp \
   controller/services/srv/cwdservice.cpp \
   controller/services/srv/listservice.cpp \
   controller/services/srv/mkdservice.cpp \
   controller/services/srv/portservice.cpp \
   controller/services/srv/pwdservice.cpp \
   controller/services/srv/retrservice.cpp \
   controller/services/srv/rmdservice.cpp \
   controller/services/srv/storservice.cpp \
   controller/services/srv/typeservice.cpp \
   controller/xmloutput/xmlcout.cpp \
   controller/xmloutput/xmlexception.cpp \
   controller/xmloutput/xmllogs.cpp \
   controller/xmloutput/xmlmessage.cpp \
   exception/namedexception.cpp \
   ftpcommand/cmds/cdupcmd.cpp \
   account/accountdatabase.cpp \
   controller/ftpconnectionworker.cpp \
   controller/replycodes/replycodes.cpp \
   ftpcommand/cmds/cwdcmd.cpp \
   ftpcommand/cmds/listcmd.cpp \
   ftpcommand/cmds/mkdcmd.cpp \
   ftpcommand/cmds/portcmd.cpp \
   ftpcommand/cmds/pwdcmd.cpp \
   ftpcommand/cmds/retrcmd.cpp \
   ftpcommand/cmds/rmdcmd.cpp \
   ftpcommand/cmds/storcmd.cpp \
   ftpcommand/cmds/typecmd.cpp \
   ftpcommand/parsers/cdupparser.cpp \
   controller/services/srv/cdupservice.cpp \
   ftpcommand/parsers/cwdparser.cpp \
   ftpcommand/parsers/listparser.cpp \
   ftpcommand/parsers/mkdparser.cpp \
   ftpcommand/parsers/portparser.cpp \
   ftpcommand/parsers/pwdparser.cpp \
   ftpcommand/parsers/retrparser.cpp \
   ftpcommand/parsers/rmdparser.cpp \
   ftpcommand/parsers/storparser.cpp \
   ftpcommand/parsers/typeparser.cpp \
   ftpfilesystem/filelocker.cpp \
   ftpfilesystem/ftpfilesystem.cpp \
   ftpcommand/ftpcommand.cpp \
   main.cpp \
   transmission/filetransmission.cpp \
   transmission/types/asciifiletransmission.cpp \
   controller/ftpcontroller.cpp \
   transmission/types/binaryfiletransmission.cpp
INCLUDEPATH += $$PWD

DISTFILES +=

STATECHARTS +=

CONFIG += c++17
