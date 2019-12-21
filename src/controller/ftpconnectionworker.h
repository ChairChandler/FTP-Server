#ifndef FTPCONNECTIONWORKER_H
#define FTPCONNECTIONWORKER_H

#include <QRunnable>
#include <memory>
#include <QObject>
#include "ftpcommand/ftpcommand.h"
#include "replycodes/replycodes.h"
#include "bsdsocket/bsdsocketfactory.h"
#include "services/FTPservice.h"

/**
* @brief Manages one ftp connection.
*/
class FTPconnectionWorker: public QObject, public QRunnable {

    private:
        Q_OBJECT

        using FactoryRef = std::unique_ptr<InterfaceBsdSocketFactory>;
        static inline auto bsdSocket = FactoryRef(new BsdSocketFactoryDefault());
        static inline auto &db = AccountDatabaseSingletonFactoryDefault().getInstance();

        int clientCommandChannel;
        static inline int timeoutMs = 20000;

        QString receiveCommandString();
        AbstractFTPservice* createService(const QString &cmd);
        bool waitForSentReply(const QString &message);
        bool sendReplyMessage(const QString &message);
        bool handleService(AbstractFTPservice * const service);
        bool isConnection();
        bool handleResponse(const QString &response);
        void printError();

    public:
        /**
        * @param clientCommandChannel Socket to communication with client on command channel.
        */
        FTPconnectionWorker(int clientCommandChannel);
        virtual ~FTPconnectionWorker() override;
        void run() override;
        static void setTimeoutMs(int value);
        static void setBsdSocketFactory(const InterfaceBsdSocketFactory &newFactory);

    signals:
        void done(int clientCommandChannel);
};

#endif // FTPCONNECTIONWORKER_H
