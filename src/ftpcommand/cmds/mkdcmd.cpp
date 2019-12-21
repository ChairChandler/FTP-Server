#include "mkdcmd.h"

MkdCmd::MkdCmd(int commandChannelSocket, const QString &path): cmdSocket(commandChannelSocket), path(path) {

}

void MkdCmd::execute() {
    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    QString rootPath = account.getFileSystem()->getRootDir().absolutePath();
    QRegExp r(QString("^") + QDir::separator());

    //if absolute path
    if(r.indexIn(path) > -1) {
        account.getFileSystem()->mkdirRelativeRootPath(path);
    } else {
        account.getFileSystem()->mkdirWD(path);
    }
}
