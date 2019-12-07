#include "accountdatabase.h"
#include <algorithm>

AccountInfo AccountDatabaseImpl::getAccountInfo(QString name) {
    AccountInfo *account = findAccount(name);
    if(isAccountCreated(account)) {
        return *account;
    } else {
        throw AccountNotFoundException();
    }
}

AccountInfo AccountDatabaseImpl::getAccountInfo(int socket) {
    AccountInfo *account = findAccount(socket);
    if(isAccountCreated(account)) {
        return *account;
    } else {
        throw AccountNotFoundException();
    }
}

void AccountDatabaseImpl::addAccountInfo(AccountInfo accountInfo) {
    AccountInfo *ac = findAccount(accountInfo.name);

    if(!isAccountCreated(ac)) {
        accounts.append(accountInfo);
    } else {
        throw AccountExistsException();
    }
}

void AccountDatabaseImpl::setAccountInfo(AccountInfo accountInfo) {
    AccountInfo *ac = findAccount(accountInfo.name);

    if(isAccountCreated(ac)) {
        *ac = accountInfo;
    } else {
        throw AccountNotFoundException();
    }
}

void AccountDatabaseImpl::resetDatabase() {
    accounts.clear();
}

AccountInfo *AccountDatabaseImpl::findAccount(QString name) {
    auto iter = std::find_if(accounts.begin(), accounts.end(), [name](AccountInfo acc){return acc.name == name;});
    AccountInfo *ac = (iter != accounts.end())? iter : nullptr;
    return ac;
}

AccountInfo *AccountDatabaseImpl::findAccount(int socket) {
    auto iter = std::find_if(accounts.begin(), accounts.end(), [socket](AccountInfo acc){return acc.commandChannelSocket == socket;});
    AccountInfo *ac = (iter != accounts.end())? iter : nullptr;
    return ac;
}

bool AccountDatabaseImpl::isAccountCreated(AccountInfo *acc) {
    return acc;
}

AccountDatabase& AccountDatabaseSingletonFactoryDefault::getInstance() {
    return *instance;
}

AccountDatabaseSingletonFactory* AccountDatabaseSingletonFactoryDefault::doClone() const {
    return new AccountDatabaseSingletonFactoryDefault(*this);
}

AccountDatabase::~AccountDatabase() {

}

AccountDatabaseSingletonFactory::~AccountDatabaseSingletonFactory() {

}
