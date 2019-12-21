#include "cdupcmd.h"

CdupCmd::CdupCmd(int commandChannelSocket): cmdSocket(commandChannelSocket) {

}

void CdupCmd::execute() {
    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    account.getFileSystem()->changeWorkingDirectoryToParent();
}
