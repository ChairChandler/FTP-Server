#include "cmduser.h"

using ADB = AccountDatabase;

CmdUser::CmdUser(QString name, int socket) {
    account.name = name;
    account.commandStreamSocket = socket;
    account.status = ADB::LoginStatus::LoggedIn;
}

void CmdUser::execute() {
    try {
        getDatabase().addAccountInfo(account);
    } catch(ADB::AccountExistsException exc) {

        ADB::AccountInfo existsAccount  = getDatabase().getAccountInfo(account.name);
        if(existsAccount.status == ADB::LoginStatus::LoggedOut) {
            getDatabase().setAccountInfo(account);
        } else {
            throw AccountIsLoggedException();
        }
    }
}

