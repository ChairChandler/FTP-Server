#include "cmdport.h"

using DB = AccountDatabase;

CmdPort::CmdPort(int commandStreamSocket, sockaddr_in address): address(address), cmdSocket(commandStreamSocket) {

}

bool CmdPort::execute() {
    try {
        DB::AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
        int dSocket = socket(AF_INET, SOCK_STREAM,0);
        if(connect(dSocket, (const sockaddr*)&address, sizeof(address))) {
            return false;
        } else {
            dataSocket = dSocket;
            return true;
        }
    } catch (DB::AccountNotFoundException exc) {
        return false;
    }
}

int CmdPort::getDataStreamSocket() {
    if(dataSocket == -1) {
        throw DataStreamSocketNotExistsException();
    } else {
        return dataSocket;
    }
}
