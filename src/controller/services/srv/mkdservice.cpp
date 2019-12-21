#include "mkdservice.h"

AbstractFTPservice::ExceptionReplyCode MkdService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    return map;
}

QString MkdService::parseReplyAfter(AbstractFTPcommand * const) {
    return QString("%1 %2 created").arg(ReplyCodes::C257.getId()).arg(path);
}

MkdService::MkdService(int commandCommunicationSocket, const QString &path):
    AbstractFTPservice(new MkdCmd(commandCommunicationSocket, path), prepareExceptionReplyCode()), path(path) {
}
