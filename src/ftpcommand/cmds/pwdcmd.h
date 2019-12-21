#ifndef PWDCMD_H
#define PWDCMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include "ftpcommand/ftpcommand.h"

/*
         PRINT WORKING DIRECTORY (PWD)

            This command causes the name of the current working
            directory to be returned in the reply.
*/

/**
 * @brief Print working directory.
 */
class PwdCmd: public AbstractFTPcommand {

    private:
        const int cmdSocket;
        QString pwd;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param dataChannelSocket Socket to communication with client on data channel
         */
        PwdCmd(int commandChannelSocket);
        void execute() override;
        QString getPwd() const;
};

#endif // PWDCMD_H
