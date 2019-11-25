#include "cmdquit.h"

using DB = AccountDatabase;

CmdQuit::CmdQuit(int commandChannelSocket): cmdSocket(commandChannelSocket) {

}

void CmdQuit::execute() {
    try {
        DB::AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
        if(account.status == DB::LoginStatus::LoggedOut) {
            throw AccountIsUnloggedException();
        }

        account.status = DB::LoginStatus::LoggedOut;
        getDatabase().setAccountInfo(account);
    } catch(DB::AccountNotFoundException &exc) {
        throw exc;
    }
}
