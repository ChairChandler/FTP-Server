#include "cmdpwd.h"
#include <unistd.h>

using ADB = AccountDatabase;

CmdPwd::CmdPwd(int commandChannelSocket, int dataChannelSocket): cmdSocket(commandChannelSocket), dataSocket(dataChannelSocket) {

}

void CmdPwd::execute() {
    try{
        AccountInfo account = getDatabase().getAccountInfo(cmdSocket);
        QString wd = account.fileSystem->printWorkingDirectory(true);
        bsdSocketFactory->write(dataSocket, wd.toStdString().c_str(), static_cast<size_t>(wd.size()) + 1);
    } catch(ADB::AccountNotFoundException) {
        throw AccountNotFoundException();
    }
}

void CmdPwd::setBsdSocketFactory(const BsdSocketFactory &newFactory) {
    bsdSocketFactory = FactoryRef(newFactory.clone());
}
