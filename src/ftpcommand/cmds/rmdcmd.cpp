#include "rmdcmd.h"

RmdCmd::RmdCmd(int commandChannelSocket, const QString &path): cmdSocket(commandChannelSocket), path(path) {

}

void RmdCmd::execute() {
    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    QString rootPath = account.getFileSystem()->getRootDir().absolutePath();
    QRegExp r(QString("^") + QDir::separator());

    //if absolute path
    if(r.indexIn(path) > -1) {
        account.getFileSystem()->rmdirRelativeRootPath(path);
    } else {
        account.getFileSystem()->rmdirWD(path);
    }
}
