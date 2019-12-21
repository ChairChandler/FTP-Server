#include "retrservice.h"

AbstractFTPservice::ExceptionReplyCode RetrService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    map[AbstractFileTransmission::FileTransmissionSendException()] = &ReplyCodes::C426;
    return map;
}

QString RetrService::parseReplyBefore(AbstractFTPcommand * const) {
    return ReplyCodes::C150.toString();
}

QString RetrService::parseReplyAfter(AbstractFTPcommand * const) {
    return ReplyCodes::C226.toString();
}

RetrService::RetrService(int commandCommunicationSocket, const QString &fileName):
    AbstractFTPservice(new RetrCmd(commandCommunicationSocket, fileName), prepareExceptionReplyCode()), fileName(fileName) {
}
