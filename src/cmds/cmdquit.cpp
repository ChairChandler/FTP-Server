#include "cmdquit.h"

using DB = AccountDatabase;

CmdQuit::CmdQuit(int commandChannelSocket): cmdSocket(commandChannelSocket) {

}

void CmdQuit::execute() {
    try {
        AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
        if(account.status == LoginStatus::LoggedOut) {
            throw AccountIsUnloggedException();
        }

        account.status = LoginStatus::LoggedOut;
        getDatabase().setAccountInfo(account);
    } catch(DB::AccountNotFoundException &exc) {
        throw exc;
    }
}
