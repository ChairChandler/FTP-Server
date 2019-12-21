#ifndef ACCOUNTDATABASE_H
#define ACCOUNTDATABASE_H

#include <QString>
#include <QVector>
#include "accountinfo.h"
#include "exception/namedexception.h"

/**
* @brief Interface for database, allow to managing accounts.
* @interface
*/
class InterfaceAccountDatabase {

    public:
        virtual void addAccountInfo(const AccountInfo &accountInfo) = 0;
        virtual AccountInfo getAccountInfo(int commandChannelSocket) = 0;
        virtual void setAccountInfo(const AccountInfo &accountInfo) = 0;
        virtual void delAccountInfo(int commandChannelSocket) = 0;
        virtual void resetDatabase() = 0;
        virtual ~InterfaceAccountDatabase();

        struct AccountNotFoundException: public NamedException {
            virtual const char* what() const noexcept override {
                return "Account not found.";
            }
            virtual QString name() override {
                return "AccountNotFoundException";
            }
        };
        struct AccountExistsException: public NamedException {
            virtual const char* what() const noexcept override {
                return "Account exists.";
            }
            virtual QString name() override {
                return "AccountExistsException";
            }
        };
};

/**
* @brief Default implementation of account database interface.
*/
class AccountDatabaseDefault: public InterfaceAccountDatabase {

    private:
        QVector<AccountInfo> accounts;

        AccountInfo* findAccount(int commandChannelSocket);
        int findAccountIndex(int commandChannelSocket);
        bool isAccountCreated(AccountInfo *acc);

    public:
        void addAccountInfo(const AccountInfo &accountInfo) override;
        AccountInfo getAccountInfo(int commandChannelSocket) override;
        void setAccountInfo(const AccountInfo &accountInfo) override;
        void delAccountInfo(int commandChannelSocket) override;
        void resetDatabase() override;
};

/**
* @brief Abstract factory, which provide access to single global account database.
* @abstract Abstract factory, which provide access to single global account database.
*/
class AbstractAccountDatabaseSingletonFactory {

    public:
        virtual InterfaceAccountDatabase& getInstance() = 0;
        virtual AbstractAccountDatabaseSingletonFactory* clone() const {
            return doClone(); //its needed in C++ in cause of not allowing to copy derived class passed by interface
        }
        virtual ~AbstractAccountDatabaseSingletonFactory() = default;

    protected:
        virtual AbstractAccountDatabaseSingletonFactory* doClone() const = 0;
};

/**
* @brief Default implementation of abstract account database singleton factory.
*/
class AccountDatabaseSingletonFactoryDefault: public AbstractAccountDatabaseSingletonFactory {

    private:
        static inline InterfaceAccountDatabase *instance = new AccountDatabaseDefault();

    public:
        virtual InterfaceAccountDatabase& getInstance() override;
        virtual AbstractAccountDatabaseSingletonFactory* doClone() const override;
};

#endif // ACCOUNTDATABASE_H
