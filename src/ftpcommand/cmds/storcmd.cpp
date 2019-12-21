#include "storcmd.h"
#include "transmission/types/asciifiletransmission.h"
#include "transmission/types/binaryfiletransmission.h"

StorCmd::StorCmd(int commandChannelSocket, const QString &fileName): cmdSocket(commandChannelSocket), fileName(fileName) {

}

void StorCmd::receive(const sockaddr_in &addr, const QString &destinationPath, AbstractFileTransmission * const trans) {
    int socket = bsdSocketFactory->socket(AF_INET, SOCK_STREAM, 0);
    bsdSocketFactory->connect(socket, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));

    QFile file(destinationPath + QDir::separator() + fileName);
    trans->receive(socket, file);

    bsdSocketFactory->close(socket);
}

void StorCmd::execute() {
    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    QString wd = account.getFileSystem()->printWorkingDirectory(false);

    if(account.getTransmissionType() == AccountInfo::TransmissionType::Ascii) {
        AsciiFileTransmission ascii;
        receive(account.getDataChannelAddress(), wd, &ascii);
    } else {
        BinaryFileTransmission binary;
        receive(account.getDataChannelAddress(), wd, &binary);
    }
}
