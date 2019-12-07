#include "ftpcontroller.h"
#include <QThreadPool>
#include "ftpconnectionworker.h"
#pragma GCC diagnostic ignored "-Wold-style-cast"

FTPcontroller::FTPcontroller(QString address, int port) {
    serverSocket = bsdSocket->socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address;

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(static_cast<uint16_t>(port));
    inet_pton(AF_INET, address.toStdString().c_str(), &server_address.sin_addr);

    if(bsdSocket->bind(serverSocket, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        throw std::runtime_error("Cannot bind server address");
    }

    if(bsdSocket->listen(serverSocket, QUEUE_SIZE) < 0) {
        throw std::runtime_error("Cannot start listening");
    }

    QObject::connect(this, &FTPcontroller::newConnection,
                     this, &FTPcontroller::handleConnection);
}

void FTPcontroller::setBsdSocketFactory(const BsdSocketFactory &newFactory) {
    bsdSocket = FactoryRef(newFactory.clone());
}

void FTPcontroller::start() {
    forever {
        int clientSocket = bsdSocket->accept(serverSocket, nullptr, nullptr);
        if(activeClients >= MAX_CLIENTS) {
            sendMaxActiveClientMessage(clientSocket);
            bsdSocket->close(clientSocket);
        } else {
            activeClients++;
            sendWelcomeMessage(clientSocket);
            emit newConnection(clientSocket);
        }
    }
}

void FTPcontroller::handleConnection(int clientSocket) {
    FTPconnectionWorker *worker = new FTPconnectionWorker(clientSocket);
    QObject::connect(worker, &FTPconnectionWorker::done,
                     this, [&](){activeClients--;});
    QThreadPool::globalInstance()->start(worker);
}

bool FTPcontroller::sendMaxActiveClientMessage(int clientSocket) {
    QByteArray array = QString("%1 %2").arg(codes.C11.getId()).arg("Connection refused due to max active users.").toUtf8() + '\r';
    return bsdSocket->write(clientSocket, array.data(), static_cast<size_t>(array.size())) > 0;
}

bool FTPcontroller::sendWelcomeMessage(int clientSocket) {
    QByteArray array = QString("%1 %2").arg(codes.C200.getId()).arg("Welcome.").toUtf8() + '\r';
    return bsdSocket->write(clientSocket, array.data(), static_cast<size_t>(array.size())) > 0;
}

