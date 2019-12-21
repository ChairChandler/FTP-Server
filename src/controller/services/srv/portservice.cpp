#include "portservice.h"

AbstractFTPservice::ExceptionReplyCode PortService::prepareExceptionReplyCode() {
    ExceptionReplyCode map;
    map[AccountDatabaseDefault::AccountNotFoundException()] = &ReplyCodes::C451;
    return map;
}

PortService::PortService(int commandChannelSocket, const sockaddr_in &address):
    AbstractFTPservice(new PortCmd(commandChannelSocket, address), prepareExceptionReplyCode()) {

}
