#ifndef FTPCONNECTIONWORKER_H
#define FTPCONNECTIONWORKER_H
#include <QRunnable>
#include <memory>
#include <QObject>
#include "ftpcommand.h"
#include "replycodes.h"
#include "bsdsocketfactory.h"
#pragma GCC diagnostic ignored "-Wpadded"

class FTPconnectionWorker: public QObject, public QRunnable {
        Q_OBJECT

        using FactoryRef = std::unique_ptr<BsdSocketFactory>;
        static inline auto bsdSocket = FactoryRef(new BsdSocketFactoryDefault());
        const ReplyCodes codes;
        int clientCommandChannel;

        QString receiveCommandString();
        FTPcommand* toCommand(QString stringCommand);
        bool sendReplyCode(QString message);

    public:
        FTPconnectionWorker(int clientCommandChannel);
        virtual ~FTPconnectionWorker() override;
        void run() override;
        static void setBsdSocketFactory(const BsdSocketFactory &newFactory);

    signals:
        void done();
};

#endif // FTPCONNECTIONWORKER_H
