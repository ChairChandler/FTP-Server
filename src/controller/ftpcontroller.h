#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H

#include <QString>
#include <QAtomicInt>
#include <memory>
#include "bsdsocket/bsdsocketfactory.h"
#include "replycodes/replycodes.h"
#include "account/accountdatabase.h"

/**
* @brief Main FTP server module.
*/
class FTPcontroller: public QObject {

    private:
        Q_OBJECT

        static const int QUEUE_SIZE = 10;
        static const int MAX_CLIENTS = 500;
        int serverSocket;
        QAtomicInt activeClients = 0;

        using FactoryRef = std::unique_ptr<InterfaceBsdSocketFactory>;
        static inline auto bsdSocket = FactoryRef(new BsdSocketFactoryDefault());
        static inline auto &db = AccountDatabaseSingletonFactoryDefault().getInstance();

        bool sendMaxActiveClientMessage(int clientSocket);
        bool sendWelcomeMessage(int clientSocket);
        void createNewAccount(const sockaddr_in &addr, int clientSocket);

    private slots:
        void handleConnection(int clientSocket);
        void cleanupConnection(int clientSocket);

    public:
        FTPcontroller(const QString &address, int port);
        [[noreturn]] void start();
        static void setBsdSocketFactory(const InterfaceBsdSocketFactory &newFactory);

    signals:
        void newConnection(int clientSocket);
};

#endif // FTPCONTROLLER_H
