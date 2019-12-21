#ifndef CDUPSERVICE_H
#define CDUPSERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/cdupcmd.h"

/*
               CDUP
                  200
                  500, 501, 502, 421, 530, 550
*/

/**
* @brief Service for handling CDUP ftp command
*/
class CdupService: public AbstractFTPservice {

    private:
        ExceptionReplyCode prepareExceptionReplyCode();
    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         */
        CdupService(int commandChannelSocket);
};

#endif // CDUPSERVICE_H
