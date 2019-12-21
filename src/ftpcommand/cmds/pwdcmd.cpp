#include "pwdcmd.h"
#include <unistd.h>
#include "ftpfilesystem/ftpfilesystem.h"

PwdCmd::PwdCmd(int commandChannelSocket): cmdSocket(commandChannelSocket) {

}

void PwdCmd::execute() {
    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    pwd = account.getFileSystem()->printWorkingDirectory(true);
}

QString PwdCmd::getPwd() const {
    return pwd;
}
