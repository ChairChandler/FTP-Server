#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QString>
#include "transmission/transmission.h"
#include "mode/mode.h"
#include "structure/structure.h"
#include "ftpfilesystem/ftpfilesystem.h"

enum struct LoginStatus {
    LoggedOut,
    LoggedIn
};

struct AccountInfo {
    QString name;
    LoginStatus status;
    int commandChannelSocket;
    int dataChannelSocket;
    Transmission *transmission;
    Mode *mode;
    Structure *structure;
    FTPfileSystem *fileSystem;

    bool operator==(const AccountInfo &a) const {
        return  name == a.name &&
                status == a.status &&
                commandChannelSocket == a.commandChannelSocket &&
                dataChannelSocket == a.dataChannelSocket &&
                transmission == a.transmission &&
                mode == a.mode &&
                structure == a.structure &&
                fileSystem == a.fileSystem;
    }

    AccountInfo(): status(LoginStatus::LoggedOut), commandChannelSocket(-1), dataChannelSocket(-1), transmission(nullptr),
    mode(nullptr), structure(nullptr), fileSystem(nullptr) {

    }
};

class AccountInfoBuilder {

    public:
        virtual int buildDataChannelSocket() const = 0;
        virtual Transmission* buildTransmission() const = 0;
        virtual Mode* buildMode() const = 0;
        virtual Structure* buildStructure() const = 0;
        virtual FTPfileSystemImpl* buildFileSystem(QString name) const = 0;
        virtual AccountInfoBuilder* clone() const;
        virtual ~AccountInfoBuilder();

    protected:
        virtual AccountInfoBuilder* doClone() const = 0;
};

class AccountInfoBuilderDefault: public AccountInfoBuilder {

    public:
        virtual int buildDataChannelSocket() const override;
        virtual Transmission* buildTransmission() const override;
        virtual Mode* buildMode() const override;
        virtual Structure* buildStructure() const override;
        virtual FTPfileSystemImpl* buildFileSystem(QString name) const override;
        virtual ~AccountInfoBuilderDefault() override;
        virtual AccountInfoBuilder* doClone() const override;
};

class AccountInfoDirector {
        const AccountInfoBuilder &builder;
    public:
        AccountInfoDirector(const AccountInfoBuilder &builder);
        AccountInfo create(QString name, LoginStatus status, int commandChannelSocket);
};

#endif // ACCOUNTINFO_H
