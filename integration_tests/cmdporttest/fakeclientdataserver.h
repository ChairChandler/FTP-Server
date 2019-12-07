#ifndef FAKECLIENTDATASERVER_H
#define FAKECLIENTDATASERVER_H
#pragma GCC diagnostic ignored "-Wpadded"

#include <QObject>
#include <QThread>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <QString>

class Server: public QObject {
    Q_OBJECT
        const sockaddr_in address;
        bool serverReady, newConnection, error;
        QString errorMsg;
    public:
        Server(const sockaddr_in &address);
        bool isServerReady() const;
        bool isNewConnection() const;
        bool isError() const;
        QString getErrorMsg() const;
        void run();
    private:
        void setError(QString what);
};

class FakeClientDataServer : public QObject
{
    Q_OBJECT

    QThread serverThread;
    Server server;
public:
    explicit FakeClientDataServer(const sockaddr_in &address, QObject *parent = nullptr);
    ~FakeClientDataServer();
    bool isServerReady() const;
    bool isNewConnection() const;
    bool isError() const;
    QString getErrorMsg() const;
};

#endif // FAKECLIENTDATASERVER_H
