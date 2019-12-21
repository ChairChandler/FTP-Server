#include "retrcmd.h"
#include "transmission/types/asciifiletransmission.h"
#include "transmission/types/binaryfiletransmission.h"

RetrCmd::RetrCmd(int commandChannelSocket, const QString &fileName): cmdSocket(commandChannelSocket), fileName(fileName) {

}

void RetrCmd::send(const sockaddr_in &addr, const QString &sourcePath, AbstractFileTransmission * const trans) {
    int socket = bsdSocketFactory->socket(AF_INET, SOCK_STREAM, 0);
    bsdSocketFactory->connect(socket, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));

    QFile file(sourcePath + QDir::separator() + fileName);
    trans->send(socket, file);

    bsdSocketFactory->close(socket);
}

void RetrCmd::execute() {
    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    QString wd = account.getFileSystem()->printWorkingDirectory(false);

    if(account.getTransmissionType() == AccountInfo::TransmissionType::Ascii) {
        AsciiFileTransmission ascii;
        send(account.getDataChannelAddress(), wd, &ascii);
    } else {
        BinaryFileTransmission binary;
        send(account.getDataChannelAddress(), wd, &binary);
    }
}
