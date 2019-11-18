#include "cmdstru.h"

using ADB = AccountDatabase;

CmdStru::CmdStru(int commandChannelSocket, FileStructure * const fileStructure): fileStructure(fileStructure), cmdSocket(commandChannelSocket) {

}

void CmdStru::execute() {
    try{
        ADB::AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
        account.fileStructure = fileStructure;
        getDatabase().setAccountInfo(account);
    } catch(ADB::AccountNotFoundException) {
        throw AccountNotFoundException();
    }
}
