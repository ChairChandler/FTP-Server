#include "accountdatabase.h"
#include <algorithm>

AccountDatabase& AccountDatabase::getInstance() {
    static AccountDatabase instance;
    return instance;
}

AccountDatabase::AccountInfo AccountDatabase::getAccountInfo(QString name) {
    AccountInfo *account = findAccount(name);
    if(isAccountCreated(account)) {
        return *account;
    } else {
        throw AccountNotFoundException();
    }
}

AccountDatabase::AccountInfo AccountDatabase::getAccountInfo(int socket) {
    AccountInfo *account = findAccount(socket);
    if(isAccountCreated(account)) {
        return *account;
    } else {
        throw AccountNotFoundException();
    }
}

void AccountDatabase::addAccountInfo(AccountDatabase::AccountInfo accountInfo) {
    AccountInfo *ac = findAccount(accountInfo.name);

    if(!isAccountCreated(ac)) {
        accounts.append(accountInfo);
    } else {
        throw AccountExistsException();
    }
}

void AccountDatabase::setAccountInfo(AccountDatabase::AccountInfo accountInfo) {
    AccountInfo *ac = findAccount(accountInfo.name);

    if(isAccountCreated(ac)) {
        *ac = accountInfo;
    } else {
        throw AccountNotFoundException();
    }
}

AccountDatabase::AccountInfo *AccountDatabase::findAccount(QString name) {
    AccountInfo *ac = std::find_if(accounts.begin(), accounts.end(), [name](AccountInfo acc){return acc.name == name;});
    return ac;
}

AccountDatabase::AccountInfo *AccountDatabase::findAccount(int socket) {
    AccountInfo *ac = std::find_if(accounts.begin(), accounts.end(), [socket](AccountInfo acc){return acc.commandStreamSocket == socket;});
    return ac;
}

bool AccountDatabase::isAccountCreated(AccountInfo *acc) {
    return acc;
}
