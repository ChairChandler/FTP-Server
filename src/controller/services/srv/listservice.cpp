#include "listservice.h"

AbstractFTPservice::ExceptionReplyCode ListService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    return map;
}

QString ListService::parseReplyAfter(AbstractFTPcommand * const) {
    return ReplyCodes::C226.toString();
}

ListService::ListService(int commandCommunicationSocket, const QString &path):
    AbstractFTPservice(new ListCmd(commandCommunicationSocket, path), prepareExceptionReplyCode()) {
}
