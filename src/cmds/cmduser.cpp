#include "cmduser.h"
#include "transmission/types/asciitransmission.h"
#include "structure/types/filestructure.h"
#include "mode/types/streammode.h"

using ADB = AccountDatabase;

CmdUser::CmdUser(QString name, int commandChannelSocket) {
    USERS_DIR.mkdir(name);

    account.name = name;
    account.commandChannelSocket = commandChannelSocket;
    account.status = ADB::LoginStatus::LoggedIn;
    account.transmission = new AsciiTransmission();
    account.structure = new FileStructure();
    account.mode = new StreamMode();
    account.fileSystem = new FTPfileSystem(QFileInfo(USERS_DIR.absolutePath() + QDir::separator() + name));
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

