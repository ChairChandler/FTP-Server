#ifndef TYPESERVICE_H
#define TYPESERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/typecmd.h"

/*
                  TYPE
                  200
                  500, 501, 504, 421, 530
 */

/**
* @brief Service for handling TYPE ftp command
*/
class TypeService: public AbstractFTPservice {

    private:
        ExceptionReplyCode prepareExceptionReplyCode();

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param type New type of transmission
        */
        TypeService(int commandChannelSocket, AccountInfo::TransmissionType type);
};

#endif // TYPESERVICE_H
