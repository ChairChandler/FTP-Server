#include "cwdservice.h"

AbstractFTPservice::ExceptionReplyCode CwdService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    return map;
}

QString CwdService::parseReplyAfter(AbstractFTPcommand * const) {
    return ReplyCodes::C250.toString();
}

CwdService::CwdService(int commandChannelSocket, const QString &path):
    AbstractFTPservice(new CwdCmd(commandChannelSocket, path), prepareExceptionReplyCode()) {

}
