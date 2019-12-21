#ifndef PWDSERVICE_H
#define PWDSERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/pwdcmd.h"

/*
                  PWD
                  257
                  500, 501, 502, 421, 550
 */

/**
* @brief Service for handling PWD ftp command
*/
class PwdService: public AbstractFTPservice {

    private:
        ExceptionReplyCode prepareExceptionReplyCode();
        virtual QString parseReplyAfter(AbstractFTPcommand * const) override;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         */
        PwdService(int commandChannelSocket);
};

#endif // PWDSERVICE_H
