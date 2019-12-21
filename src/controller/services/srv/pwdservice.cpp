#include "pwdservice.h"

AbstractFTPservice::ExceptionReplyCode PwdService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    return map;
}

QString PwdService::parseReplyAfter(AbstractFTPcommand * const cmd) {
    PwdCmd *pwd = dynamic_cast<PwdCmd*>(cmd);
    QMap<QString, QString> m;
    return QString("%1 %2").arg(ReplyCodes::C257.getId()).arg(pwd->getPwd());
}

PwdService::PwdService(int commandChannelSocket):
    AbstractFTPservice(new PwdCmd(commandChannelSocket), prepareExceptionReplyCode()) {

}
