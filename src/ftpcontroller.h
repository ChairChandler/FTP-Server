#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H
#include <netinet/ip.h>
#include <QString>
#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include "ReplyCodes.h"


class FTPcontroller: public QObject
{
    Q_OBJECT
private:
    const int QUEUE_SIZE = 10;
    const int BUFF_SIZE = 512;
    const ReplyCodes codes;
    int serverSocket;
    bool sendReplyCode(int clientSocket, QString code);

public:
    FTPcontroller(QString address, int port);


signals:
    void start();
    void newConnection(int clientSocket);

private slots:
    void handleConnection(int clientSocket);
    void loop();
};

#endif // FTPCONTROLLER_H
