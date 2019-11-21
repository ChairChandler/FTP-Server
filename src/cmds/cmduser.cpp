#include "cmduser.h"
#include "transmission/types/asciitransmission.h"

using ADB = AccountDatabase;

CmdUser::CmdUser(QString name, int commandChannelSocket) {
    account.name = name;
    account.commandChannelSocket = commandChannelSocket;
    account.status = ADB::LoginStatus::LoggedIn;
    account.transmission = new AsciiTransmission();
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

