#include "accountinfo.h"
#include "transmission/types/asciitransmission.h"
#include "structure/types/filestructure.h"
#include "mode/types/streammode.h"

AccountInfoBuilder *AccountInfoBuilder::clone() const {
    return doClone();
}

AccountInfoBuilder::~AccountInfoBuilder() {

}

int AccountInfoBuilderDefault::buildDataChannelSocket() const {
    return -1;
}

Transmission *AccountInfoBuilderDefault::buildTransmission() const {
    return new AsciiTransmission();
}

Mode *AccountInfoBuilderDefault::buildMode() const {
    return new StreamMode();
}

Structure *AccountInfoBuilderDefault::buildStructure() const {
    return new FileStructure();
}

FTPfileSystemImpl *AccountInfoBuilderDefault::buildFileSystem(QString name) const {
    static QDir USERS_DIR = QDir().absolutePath() + QDir::separator() + "Users";
    if(!USERS_DIR.exists()) {
        QDir().mkdir("Users");
    }
    USERS_DIR.mkdir(name);
    return new FTPfileSystemImpl(QFileInfo(USERS_DIR.absolutePath() + QDir::separator() + name));
}

AccountInfoBuilderDefault::~AccountInfoBuilderDefault() {

}

AccountInfoBuilder* AccountInfoBuilderDefault::doClone() const {
    return new AccountInfoBuilderDefault(*this);
}

AccountInfoDirector::AccountInfoDirector(const AccountInfoBuilder &builder): builder(builder) {

}

AccountInfo AccountInfoDirector::create(QString name, LoginStatus status, int commandChannelSocket) {
    AccountInfo account;

    account.name = name;
    account.status = status;
    account.commandChannelSocket = commandChannelSocket;
    account.mode = builder.buildMode();
    account.structure = builder.buildStructure();
    account.fileSystem = builder.buildFileSystem(name);
    account.transmission = builder.buildTransmission();
    account.dataChannelSocket = builder.buildDataChannelSocket();

    return account;
}
