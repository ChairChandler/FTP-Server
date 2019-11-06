#ifndef CMDUSER_H
#define CMDUSER_H
#include "ftpcommand.h"
#include <QString>

/**
 * @brief Creates a new account or sign in a client
 */
class CmdUser: public FTPcommand {

    private:
        AccountDatabase::AccountInfo account;

    public:
        /**
         * @brief CmdUser
         * @param name Client name
         * @param socket Socket to communication with client on command stream
         */
        CmdUser(QString name, int socket);
        bool execute() override;
};

#endif // CMDUSER_H
