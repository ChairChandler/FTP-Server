#include "typecmd.h"

TypeCmd::TypeCmd(int commandChannelSocket, AccountInfo::TransmissionType newTransmissionType): transmission(newTransmissionType), cmdSocket(commandChannelSocket) {

}

void TypeCmd::execute() {
    AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
    account.setTransmissionType(transmission);
    getDatabase().setAccountInfo(account);
}


