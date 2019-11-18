#include "cmdmode.h"

using ADB = AccountDatabase;

CmdMode::CmdMode(int commandChannelSocket, Mode * const mode): mode(mode), cmdSocket(commandChannelSocket) {

}

void CmdMode::execute() {
    try{
        ADB::AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
        account.mode = mode;
        getDatabase().setAccountInfo(account);
    } catch(ADB::AccountNotFoundException) {
        throw AccountNotFoundException();
    }
}
