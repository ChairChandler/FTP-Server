#ifndef CMDQUIT_H
#define CMDQUIT_H
#include "ftpcommand.h"

/**
 * @brief Sign out a logged client
 */
class CmdQuit: public FTPcommand {

    private:
        const int socket;

    public:
        /**
         * @brief CmdQuit
         * @param socket Socket to communication with client on command stream
         */
        CmdQuit(int socket);
        void execute() override;

        using AccountNotFoundException = AccountDatabase::AccountNotFoundException;
        struct AccountIsUnloggedException: std::exception {};
};

#endif // CMDQUIT_H
