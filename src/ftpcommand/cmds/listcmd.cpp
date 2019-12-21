#include "listcmd.h"

ListCmd::ListCmd(int commandCommunicationSocket, const QString &path): cmdSocket(commandCommunicationSocket), path(path) {

}

void ListCmd::send(const QStringList &filesInfo, const sockaddr_in &addr) {
    int socket = bsdSocketFactory->socket(AF_INET, SOCK_STREAM, 0);
    bsdSocketFactory->connect(socket, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));

    for(QString s: filesInfo) {
        bsdSocketFactory->write(socket, s.toUtf8(), static_cast<size_t>(s.size()));
    }

    bsdSocketFactory->close(socket);
}

void ListCmd::execute() {
    QStringList data;

    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    if(path.isEmpty()) {
        data = account.getFileSystem()->getLinuxFilesInfoListInWorkingDirectory();
    } else {
        QFileInfo file(account.getFileSystem()->getRootDir().path() + path);
        if(file.isDir()) {
            data = account.getFileSystem()->getLinuxFilesInfoListInRelativePath(path);
        }
    }

    send(data, account.getDataChannelAddress());
}

void ListCmd::setBsdSocketFactory(const InterfaceBsdSocketFactory &newBsdSocketFactory) {
    bsdSocketFactory = FactoryRef(newBsdSocketFactory.clone());
}
