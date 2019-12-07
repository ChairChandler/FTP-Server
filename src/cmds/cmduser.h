#ifndef CMDUSER_H
#define CMDUSER_H
#include "ftpcommand.h"
#include <QString>

/*
         USER NAME (USER)

            The argument field is a Telnet string identifying the user.
            The user identification is that which is required by the
            server for access to its file system.  This command will
            normally be the first command transmitted by the user after
            the control connections are made (some servers may require
            this).  Additional identification information in the form of
            a password and/or an account command may also be required by
            some servers.  Servers may allow a new USER command to be
            entered at any point in order to change the access control
            and/or accounting information.  This has the effect of
            flushing any user, password, and account information already
            supplied and beginning the login sequence again.  All
            transfer parameters are unchanged and any file transfer in
            progress is completed under the old access control
            parameters.

*/

/**
 * @brief Creates a new account or sign in a client
 */
class CmdUser: public FTPcommand {

    private:
        AccountInfo account;
        using BuilderRef = std::unique_ptr<AccountInfoBuilder>;
        static inline auto builder = BuilderRef(new AccountInfoBuilderDefault);

    public:
        /**
         * @brief CmdUser
         * @param name Client name
         * @param commandChannelSocket Socket to communication with client on command channel
         */
        CmdUser(QString name, int commandChannelSocket);
        void execute() override;
        static void setAccountInfoBuilder(const AccountInfoBuilder &newBuilder);

        struct AccountIsLoggedException: std::exception {};


};

#endif // CMDUSER_H
