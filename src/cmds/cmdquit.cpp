#include "cmdquit.h"

using DB = AccountDatabase;

CmdQuit::CmdQuit(int commandChannelSocket): commandStreamSocket(commandChannelSocket) {

}

void CmdQuit::execute() {
    try {
        DB::AccountInfo account = getDatabase().getAccountInfo(commandStreamSocket);
        if(account.status == DB::LoginStatus::LoggedOut) {
            throw AccountIsUnloggedException();
        }

        account.status = DB::LoginStatus::LoggedOut;
        getDatabase().setAccountInfo(account);
    } catch(DB::AccountNotFoundException &exc) {
        throw exc;
    }
}
