#include "portcmd.h"

PortCmd::PortCmd(int commandChannelSocket, sockaddr_in address): address(address), cmdSocket(commandChannelSocket) {

}

void PortCmd::execute() {
    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    account.setDataChannelAddress(address);
    getDatabase().setAccountInfo(account);
}
