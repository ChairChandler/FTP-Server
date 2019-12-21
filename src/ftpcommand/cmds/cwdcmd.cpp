#include "cwdcmd.h"

CwdCmd::CwdCmd(int commandChannelSocket, const QString &path): cmdSocket(commandChannelSocket), path(path) {

}

void CwdCmd::execute() {
    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    QString rootPath = account.getFileSystem()->getRootDir().absolutePath();
    QRegExp r(QString("^") + QDir::separator());

    //if absolute path
    if(r.indexIn(path) > -1) {
        account.getFileSystem()->changeRelativeRootWorkingDirectory(path);
    } else {
        account.getFileSystem()->changeRelativeCurrentWorkingDirectory(path);
    }
}
