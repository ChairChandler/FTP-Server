#include "typeservice.h"

AbstractFTPservice::ExceptionReplyCode TypeService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    return map;
}

TypeService::TypeService(int commandChannelSocket, AccountInfo::TransmissionType type):
    AbstractFTPservice(new TypeCmd(commandChannelSocket, type), prepareExceptionReplyCode()) {

}
