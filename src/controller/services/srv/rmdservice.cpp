#include "rmdservice.h"

AbstractFTPservice::ExceptionReplyCode RmdService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    return map;
}

QString RmdService::parseReplyAfter(AbstractFTPcommand * const) {
    return ReplyCodes::C250.toString();
}

RmdService::RmdService(int commandCommunicationSocket, const QString &path):
    AbstractFTPservice(new RmdCmd(commandCommunicationSocket, path), prepareExceptionReplyCode()), path(path) {
}
