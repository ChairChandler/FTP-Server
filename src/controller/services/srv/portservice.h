#ifndef PORTSERVICE_H
#define PORTSERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/portcmd.h"

/*
                  PORT
                  200
                  500, 501, 421, 530

 */

/**
* @brief Service for handling PORT ftp command
*/
class PortService: public AbstractFTPservice {

    private:
        ExceptionReplyCode prepareExceptionReplyCode();

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param address Data channel client address
        */
        PortService(int commandChannelSocket, const sockaddr_in &address);
};

#endif // PORTSERVICE_H
