#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QString>
#include <QFileInfo>
#include <memory>
#include <netinet/ip.h>
#include "ftpfilesystem/ftpfilesystem.h"

/**
* @brief Structure for handle ftp user information.
*/
class AccountInfo {

    public:
        enum struct TransmissionType {
            Ascii,
            Binary
        };

    private:
        using SmartFTPfileSystem = std::shared_ptr<InterfaceFTPfileSystem>;

        sockaddr_in commandChannelAddress;
        sockaddr_in dataChannelAddress;
        int commandChannelSocket;
        TransmissionType transmissionType;
        SmartFTPfileSystem fileSystem;

        //default root path is the directory of executable ftp server
        static inline auto defaultRootPath = QFileInfo(QDir().path());

    public:
        AccountInfo();

        sockaddr_in getCommandChannelAddress() const;
        void setCommandChannelAddress(const sockaddr_in &value);

        sockaddr_in getDataChannelAddress() const;
        void setDataChannelAddress(const sockaddr_in &value);

        int getCommandChannelSocket() const;
        void setCommandChannelSocket(int value);

        TransmissionType getTransmissionType() const;
        void setTransmissionType(const TransmissionType &value);

        InterfaceFTPfileSystem* getFileSystem() const;

        static QFileInfo getDefaultRootPath();
        /**
        * @brief Have to be done before server is running.
        */
        static void setDefaultRootPath(const QFileInfo &value);
};

#endif // ACCOUNTINFO_H
