#include "cmduser.h"

using ADB = AccountDatabase;

CmdUser::CmdUser(QString name, int socket) {
    account.name = name;
    account.commandStreamSocket = socket;
    account.status = ADB::LoginStatus::LoggedIn;
}

bool CmdUser::execute() {
    try {
        getDatabase().addAccountInfo(account);
        return true;

    } catch(ADB::AccountExistsException exc) {

        ADB::AccountInfo existsAccount  = getDatabase().getAccountInfo(account.name);
        if(existsAccount.status == ADB::LoginStatus::LoggedOut) {
            getDatabase().setAccountInfo(account);
            return true;
        } else {
            return false;
        }
    }
}

