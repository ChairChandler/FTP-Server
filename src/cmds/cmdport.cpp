#include "cmdport.h"
#pragma GCC diagnostic ignored "-Wold-style-cast"

using DB = AccountDatabase;

CmdPort::CmdPort(int commandChannelSocket, sockaddr_in address): address(address), cmdSocket(commandChannelSocket) {

}

void CmdPort::execute() {
    try {
        AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
        int dSocket = bsdSocketFactory->socket(AF_INET, SOCK_STREAM, 0);

        if(bsdSocketFactory->connect(dSocket, (const sockaddr*)&address, sizeof(address))) {
            throw CannotConnectException();
        } else {
            dataSocket = dSocket;
        }
    } catch (DB::AccountNotFoundException &exc) {
        throw exc;
    }
}

int CmdPort::getDataChannelSocket() const {
    if(dataSocket == -1) {
        throw DataChannelSocketNotExistsException();
    } else {
        return dataSocket;
    }
}

void CmdPort::setBsdSocketFactory(const BsdSocketFactory &newBsdSocketFactory) {
    bsdSocketFactory = FactoryRef(newBsdSocketFactory.clone());
}
