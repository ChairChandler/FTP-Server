#ifndef CMDQUIT_H
#define CMDQUIT_H
#pragma GCC diagnostic ignored "-Wpadded"
#include "ftpcommand.h"

/*
         LOGOUT (QUIT)

            This command terminates a USER and if file transfer is not
            in progress, the server closes the control connection.  If
            file transfer is in progress, the connection will remain
            open for result response and the server will then close it.
            If the user-process is transferring files for several USERs
            but does not wish to close and then reopen connections for
            each, then the REIN command should be used instead of QUIT.

            An unexpected close on the control connection will cause the
            server to take the effective action of an abort (ABOR) and a
            logout (QUIT).
*/


/**
 * @brief Sign out a logged client
 */
class CmdQuit: public FTPcommand {

    private:
        const int cmdSocket;

    public:
        /**
         * @brief CmdQuit
         * @param commandChannelSocket Socket to communication with client on command channel
         */
        CmdQuit(int commandChannelSocket);
        void execute() override;

        using AccountNotFoundException = AccountDatabase::AccountNotFoundException;
        struct AccountIsUnloggedException: std::exception {};
};

#endif // CMDQUIT_H
