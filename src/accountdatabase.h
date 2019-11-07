#ifndef ACCOUNTDATABASE_H
#define ACCOUNTDATABASE_H
#include <QString>
#include <QVector>

class AccountDatabase {

    public:
        enum struct LoginStatus {
            LoggedOut,
            LoggedIn
        };

        struct AccountInfo {
            QString name;
            LoginStatus status;
            int commandStreamSocket;
            int dataStreamSocket;

            bool operator==(const AccountInfo &a) const {
                return  name == a.name &&
                        status == a.status &&
                        commandStreamSocket == a.commandStreamSocket &&
                        dataStreamSocket == a.dataStreamSocket;
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
