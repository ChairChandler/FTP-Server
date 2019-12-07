#include "ftpconnectionworker.h"

FTPconnectionWorker::FTPconnectionWorker(int clientCommandChannel): clientCommandChannel(clientCommandChannel) {

}

FTPconnectionWorker::~FTPconnectionWorker() {
    emit done();
}

void FTPconnectionWorker::run() {
    FTPcommand *cmd = toCommand(receiveCommandString());

    forever {
        try {
            cmd->execute();
        } catch(...) {

        }
    }
}

void FTPconnectionWorker::setBsdSocketFactory(const BsdSocketFactory &newFactory) {
    bsdSocket = FactoryRef(newFactory.clone());
}

QString FTPconnectionWorker::receiveCommandString() {
    QByteArray array(1024, '\0');
    bsdSocket->read(clientCommandChannel, array.data(), static_cast<size_t>(array.size()));
    return array;
}

FTPcommand* FTPconnectionWorker::toCommand(QString stringCommand) {

}

bool FTPconnectionWorker::sendReplyCode(QString message) {
    QByteArray array = message.toUtf8() + '\r';
    return bsdSocket->write(clientCommandChannel, array.data(), static_cast<size_t>(array.size())) > 0;
}
