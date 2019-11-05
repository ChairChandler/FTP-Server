#include "cmdquit.h"

using DB = AccountDatabase;

CmdQuit::CmdQuit(int socket): socket(socket) {

}

bool CmdQuit::execute() {
    try {
        DB::AccountInfo account = getDatabase().getAccountInfo(socket);
        account.status = DB::LoginStatus::LoggedOut;
        getDatabase().setAccountInfo(account);
        return true;

    } catch(DB::AccountNotFoundException exc) {
        return false;
    }
}
