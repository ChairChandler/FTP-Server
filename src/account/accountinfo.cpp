#include "accountinfo.h"

AccountInfo::AccountInfo() {
    commandChannelAddress.sin_addr.s_addr = 0;
    commandChannelAddress.sin_port = 0;
    commandChannelAddress.sin_family = 0;
    memset(commandChannelAddress.sin_zero, 0, 8); //have to be fulfilment by 0

    dataChannelAddress.sin_addr.s_addr = 0;
    dataChannelAddress.sin_port = 0;
    dataChannelAddress.sin_family = 0;
    memset(dataChannelAddress.sin_zero, 0, 8); //have to be fulfilment by 0

    commandChannelSocket = -1;
    transmissionType = TransmissionType::Ascii;
    fileSystem = SmartFTPfileSystem(new FTPfileSystemDefault(defaultRootPath));
}

sockaddr_in AccountInfo::getCommandChannelAddress() const {
    return commandChannelAddress;
}

void AccountInfo::setCommandChannelAddress(const sockaddr_in &value) {
    commandChannelAddress = value;
}

sockaddr_in AccountInfo::getDataChannelAddress() const {
    return dataChannelAddress;
}

void AccountInfo::setDataChannelAddress(const sockaddr_in &value) {
    dataChannelAddress = value;
}

int AccountInfo::getCommandChannelSocket() const {
    return commandChannelSocket;
}

void AccountInfo::setCommandChannelSocket(int value) {
    commandChannelSocket = value;
}

AccountInfo::TransmissionType AccountInfo::getTransmissionType() const {
    return transmissionType;
}

void AccountInfo::setTransmissionType(const TransmissionType &value) {
    transmissionType = value;
}

InterfaceFTPfileSystem *AccountInfo::getFileSystem() const {
    return fileSystem.get();
}

QFileInfo AccountInfo::getDefaultRootPath() {
    return defaultRootPath;
}

void AccountInfo::setDefaultRootPath(const QFileInfo &value) {
    defaultRootPath = value;
}
