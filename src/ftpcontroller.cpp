#include "ftpcontroller.h"
#include <arpa/inet.h>
#include <qdebug.h>
#include <unistd.h>
#include <algorithm>

FTPcontroller::FTPcontroller(QString address, int port)
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address;

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(static_cast<uint16_t>(port));
    inet_pton(AF_INET, address.toStdString().c_str(), &server_address.sin_addr);

    if(bind(serverSocket, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        throw std::runtime_error("Cannot bind server address");
    }

    if(listen(serverSocket, QUEUE_SIZE) < 0) {
        throw std::runtime_error("Cannot start listening");
    }

    QObject::connect(this, &FTPcontroller::start,
                     this, &FTPcontroller::loop);

    QObject::connect(this, &FTPcontroller::newConnection,
                     this, &FTPcontroller::handleConnection);
}

void FTPcontroller::loop()
{
    QtConcurrent::run([this](){

        while(true)
        {
            int clientSocket = accept(serverSocket, nullptr, nullptr);
            emit newConnection(clientSocket);
        }
    });
}

void FTPcontroller::handleConnection(int clientSocket)
{
    QtConcurrent::run([this, clientSocket](){

        qDebug() << "New client!\n";
        while(!sendReplyCode(clientSocket, codes.C220)) {
            qDebug() << "Couldn't write reply code to client!\n";
        }
    });
}

bool FTPcontroller::sendReplyCode(int clientSocket, QString code)
{
    std::array<char, BUFF_SIZE> buff;
    std::copy(code.begin(), code.end(), buff);
    return write(clientSocket, buff.data(), BUFF_SIZE) > 0;
}
