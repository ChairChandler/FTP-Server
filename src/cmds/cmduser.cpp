#include "cmduser.h"
#include "accountinfo.h"

using ADB = AccountDatabase;

CmdUser::CmdUser(QString name, int commandChannelSocket) {

    AccountInfoDirector director(*builder);

    account = director.create(name, LoginStatus::LoggedIn, commandChannelSocket);
}

void CmdUser::execute() {
    try {
        getDatabase().addAccountInfo(account);
    } catch(ADB::AccountExistsException exc) {

        AccountInfo existsAccount  = getDatabase().getAccountInfo(account.name);
        if(existsAccount.status == LoginStatus::LoggedOut) {
            getDatabase().setAccountInfo(account);
        } else {
            throw AccountIsLoggedException();
        }
    }
}

void CmdUser::setAccountInfoBuilder(const AccountInfoBuilder &newBuilder) {
    builder = BuilderRef(newBuilder.clone());
}

