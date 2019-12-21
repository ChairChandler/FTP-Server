#ifndef RMDSERVICE_H
#define RMDSERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/rmdcmd.h"

/*
               RMD
                  250
                  500, 501, 502, 421, 530, 550
*/

/**
* @brief Service for handling RMD ftp command
*/
class RmdService: public AbstractFTPservice {

    private:
        const QString path;
        AbstractFTPservice::ExceptionReplyCode prepareExceptionReplyCode();
        virtual QString parseReplyAfter(AbstractFTPcommand * const) override;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param path Path or name of the directory
        */
        RmdService(int commandCommunicationSocket, const QString &path);
};

#endif // RMDSERVICE_H
