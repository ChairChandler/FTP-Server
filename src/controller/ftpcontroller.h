#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H
#include <QString>
#include <QObject>
#include <memory>
#include "bsdsocketfactory.h"
#include "replycodes.h"
#include <QAtomicInt>
#pragma GCC diagnostic ignored "-Wpadded"

class FTPcontroller: public QObject {
    Q_OBJECT
    static const int QUEUE_SIZE = 10;
    static const int MAX_CLIENTS = 2; //TODO
    static const inline ReplyCodes codes;
    int serverSocket;
    QAtomicInt activeClients = 0;
    using FactoryRef = std::unique_ptr<BsdSocketFactory>;
    static inline auto bsdSocket = FactoryRef(new BsdSocketFactoryDefault());

public:
    FTPcontroller(QString address, int port);
    [[noreturn]] void start();
    static void setBsdSocketFactory(const BsdSocketFactory &newFactory);

signals:
    void newConnection(int clientSocket);

private slots:
    void handleConnection(int clientSocket);

private:
    bool sendMaxActiveClientMessage(int clientSocket);
    bool sendWelcomeMessage(int clientSocket);
};

#endif // FTPCONTROLLER_H
