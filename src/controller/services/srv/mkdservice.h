#ifndef MKDSERVICE_H
#define MKDSERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/mkdcmd.h"

/*
               MKD
                  257
                  500, 501, 502, 421, 530, 550
*/

/**
* @brief Service for handling MKD ftp command
*/
class MkdService: public AbstractFTPservice {

    private:
        const QString path;
        AbstractFTPservice::ExceptionReplyCode prepareExceptionReplyCode();
        virtual QString parseReplyAfter(AbstractFTPcommand * const) override;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param path Path or name of the file
        */
        MkdService(int commandCommunicationSocket, const QString &path);
};

#endif // MKDSERVICE_H
