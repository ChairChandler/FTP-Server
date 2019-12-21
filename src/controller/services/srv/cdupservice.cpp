#include "cdupservice.h"

AbstractFTPservice::ExceptionReplyCode CdupService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    return map;
}

CdupService::CdupService(int commandChannelSocket):
    AbstractFTPservice(new CdupCmd(commandChannelSocket), prepareExceptionReplyCode()) {

}
