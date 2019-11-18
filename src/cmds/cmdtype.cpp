#include "cmdtype.h"

using ADB = AccountDatabase;

CmdType::CmdType(int commandChannelSocket, Transmission * const transmission): transmission(transmission), cmdSocket(commandChannelSocket) {

}

void CmdType::execute() {
    try{
        ADB::AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
        account.transmission = transmission;
        getDatabase().setAccountInfo(account);
    } catch(ADB::AccountNotFoundException) {
        throw AccountNotFoundException();
    }
}


