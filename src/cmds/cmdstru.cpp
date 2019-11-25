#include "cmdstru.h"

using ADB = AccountDatabase;

CmdStru::CmdStru(int commandChannelSocket, Structure * const fileStructure): structure(fileStructure), cmdSocket(commandChannelSocket) {

}

void CmdStru::execute() {
    try{
        ADB::AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
        account.structure = structure;
        getDatabase().setAccountInfo(account);
    } catch(ADB::AccountNotFoundException) {
        throw AccountNotFoundException();
    }
}
