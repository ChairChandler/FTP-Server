#ifndef ACCOUNTDATABASE_H
#define ACCOUNTDATABASE_H
#include <QString>
#include <QVector>
#include "accountinfo.h"

class AccountDatabase {

    public:
        virtual AccountInfo getAccountInfo(QString name) = 0;
        virtual AccountInfo getAccountInfo(int socket) = 0;
        virtual void addAccountInfo(AccountInfo accountInfo) = 0;
        virtual void setAccountInfo(AccountInfo accountInfo) = 0;
        virtual void resetDatabase() = 0;
        virtual ~AccountDatabase();

        struct AccountNotFoundException: std::exception {};
        struct AccountExistsException: std::exception {};
};

class AccountDatabaseImpl: public AccountDatabase {

    private:
        QVector<AccountInfo> accounts;

        AccountInfo* findAccount(QString name);
        AccountInfo* findAccount(int socket);
        bool isAccountCreated(AccountInfo*);

    public:
        AccountDatabaseImpl() = default;
        AccountInfo getAccountInfo(QString name) override;
        AccountInfo getAccountInfo(int socket) override;
        void addAccountInfo(AccountInfo accountInfo) override;
        void setAccountInfo(AccountInfo accountInfo) override;
        void resetDatabase() override;
        ~AccountDatabaseImpl() override = default;
};

class AccountDatabaseSingletonFactory {

    public:
        virtual AccountDatabase& getInstance() = 0;
        virtual AccountDatabaseSingletonFactory* clone() const {
            return doClone();
        }
        virtual ~AccountDatabaseSingletonFactory();

    protected:
        virtual AccountDatabaseSingletonFactory* doClone() const = 0;
};

class AccountDatabaseSingletonFactoryDefault: public AccountDatabaseSingletonFactory {
        static inline AccountDatabase *instance = new AccountDatabaseImpl();
    public:
        virtual AccountDatabase& getInstance() override;
        virtual AccountDatabaseSingletonFactory* doClone() const override;
        virtual ~AccountDatabaseSingletonFactoryDefault() override = default;
};

#endif // ACCOUNTDATABASE_H
