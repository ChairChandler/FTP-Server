#ifndef CMDTYPE_H
#define CMDTYPE_H
#pragma GCC diagnostic ignored "-Wpadded"
#include "ftpcommand.h"
#include "transmission//transmission.h"

/**
 * @brief Change type of transmission
 */
class CmdType: public FTPcommand {

    private:
        Transmission * const transmission;
        int cmdSocket;

    public:
        /**
         * @brief CmdQuit
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param transmission Type of transmission
         */
        CmdType(int commandChannelSocket, Transmission * const transmission);
        void execute() override;

        using AccountNotFoundException = AccountDatabase::AccountNotFoundException;
};

#endif // CMDTYPE_H
