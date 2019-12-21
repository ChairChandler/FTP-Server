#ifndef CWDSERVICE_H
#define CWDSERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/cwdcmd.h"

/*
               CWD
                  250
                  500, 501, 502, 421, 530, 550
*/

/**
* @brief Service for handling CWD ftp command
*/
class CwdService: public AbstractFTPservice {

    private:
        ExceptionReplyCode prepareExceptionReplyCode();
        virtual QString parseReplyAfter(AbstractFTPcommand * const) override;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param path Path or name of the directory
        */
        CwdService(int commandChannelSocket, const QString &path);
};

#endif // CWDSERVICE_H
