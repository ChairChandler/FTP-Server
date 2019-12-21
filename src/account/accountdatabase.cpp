#include "accountdatabase.h"
#include <algorithm>

void AccountDatabaseDefault::addAccountInfo(const AccountInfo &accountInfo) {
    AccountInfo *ac = findAccount(accountInfo.getCommandChannelSocket());

    if(!isAccountCreated(ac)) {
        accounts.append(accountInfo);
    } else {
        throw AccountExistsException();
    }
}

AccountInfo AccountDatabaseDefault::getAccountInfo(int commandChannelSocket) {
    AccountInfo *account = findAccount(commandChannelSocket);

    if(isAccountCreated(account)) {
        return *account;
    } else {
        throw AccountNotFoundException();
    }
}

void AccountDatabaseDefault::setAccountInfo(const AccountInfo &accountInfo) {
    AccountInfo *ac = findAccount(accountInfo.getCommandChannelSocket());

    if(isAccountCreated(ac)) {
        *ac = accountInfo;
    } else {
        throw AccountNotFoundException();
    }
}

void AccountDatabaseDefault::delAccountInfo(int commandChannelSocket) {
    int indx = findAccountIndex(commandChannelSocket);

    if(indx > -1) {
        accounts.remove(indx);
    } else {
        throw AccountNotFoundException();
    }
}

void AccountDatabaseDefault::resetDatabase() {
    accounts.clear();
}

AccountInfo* AccountDatabaseDefault::findAccount(int commandChannelSocket) {
    auto iter = std::find_if(accounts.begin(), accounts.end(), [commandChannelSocket](AccountInfo acc){return acc.getCommandChannelSocket() == commandChannelSocket;});
    AccountInfo *ac = (iter != accounts.end())? iter : nullptr; //nullptr means not found
    return ac;
}

int AccountDatabaseDefault::findAccountIndex(int commandChannelSocket) {
    for(int i=0; i<accounts.size(); i++) {
        if(accounts[i].getCommandChannelSocket() == commandChannelSocket) {
            return i;
        }
    }

    return -1; //value -1 means not found
}

bool AccountDatabaseDefault::isAccountCreated(AccountInfo *acc) {
    return acc;
}

InterfaceAccountDatabase& AccountDatabaseSingletonFactoryDefault::getInstance() {
    return *instance;
}

AbstractAccountDatabaseSingletonFactory* AccountDatabaseSingletonFactoryDefault::doClone() const {
    return new AccountDatabaseSingletonFactoryDefault(*this);
}

InterfaceAccountDatabase::~InterfaceAccountDatabase() {

}
