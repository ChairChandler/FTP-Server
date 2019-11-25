#ifndef ACCOUNTDATABASE_H
#define ACCOUNTDATABASE_H
#include <QString>
#include <QVector>
#include "transmission/transmission.h"
#include "mode/mode.h"
#include "structure/structure.h"
#include "ftpfilesystem/ftpfilesystem.h"


class AccountDatabase {

    public:
        enum struct LoginStatus {
            LoggedOut,
            LoggedIn
        };

        struct AccountInfo {
            QString name;
            LoginStatus status;
            int commandChannelSocket;
            int dataChannelSocket;
            Transmission *transmission;
            Mode *mode;
            Structure *structure;
            FTPfileSystem *fileSystem;

            bool operator==(const AccountInfo &a) const {
                return  name == a.name &&
                        status == a.status &&
                        commandChannelSocket == a.commandChannelSocket &&
                        dataChannelSocket == a.dataChannelSocket &&
                        transmission == a.transmission &&
                        mode == a.mode &&
                        structure == a.structure &&
                        fileSystem == a.fileSystem;
            }

            AccountInfo(): status(LoginStatus::LoggedOut), commandChannelSocket(-1), dataChannelSocket(-1), transmission(nullptr),
            mode(nullptr), structure(nullptr), fileSystem(nullptr) {

            }
        };

    private:
        QVector<AccountInfo> accounts;

        AccountInfo* findAccount(QString name);
        AccountInfo* findAccount(int socket);
        bool isAccountCreated(AccountInfo*);

    public:
        static AccountDatabase& getInstance();
        AccountInfo getAccountInfo(QString name);
        AccountInfo getAccountInfo(int socket);
        void addAccountInfo(AccountInfo accountInfo);
        void setAccountInfo(AccountInfo accountInfo);
        void resetDatabase();


        struct AccountNotFoundException: std::exception {};
        struct AccountExistsException: std::exception {};
};

#endif // ACCOUNTDATABASE_H
