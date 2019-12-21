#include "storservice.h"

AbstractFTPservice::ExceptionReplyCode StorService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    map[AbstractFileTransmission::FileTransmissionReceiveException()] = &ReplyCodes::C426;
    return map;
}

QString StorService::parseReplyBefore(AbstractFTPcommand * const) {
    return ReplyCodes::C150.toString();
}

QString StorService::parseReplyAfter(AbstractFTPcommand * const) {
    return ReplyCodes::C226.toString();
}

StorService::StorService(int commandCommunicationSocket, const QString &fileName):
    AbstractFTPservice(new StorCmd(commandCommunicationSocket, fileName), prepareExceptionReplyCode()), fileName(fileName) {
}
