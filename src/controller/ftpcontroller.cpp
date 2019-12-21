#include "ftpcontroller.h"
#include <QThreadPool>
#include "xmloutput/xmlcout.h"
#include "xmloutput/xmlexception.h"
#include "ftpconnectionworker.h"

FTPcontroller::FTPcontroller(const QString &address, int port) {
    XmlCout("server").
            key("phase").value("init").
            key("status").value("started");

    serverSocket = bsdSocket->socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address;

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(static_cast<uint16_t>(port));
    inet_pton(AF_INET, address.toStdString().c_str(), &server_address.sin_addr);

    char reuse_addr_val = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, static_cast<char*>(&reuse_addr_val), sizeof(reuse_addr_val));
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, static_cast<char*>(&reuse_addr_val), sizeof(reuse_addr_val));

    if(bsdSocket->bind(serverSocket, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0) {
        throw XmlException("server").
                key("bind").
                key("phase").value("init").
                key("status").value("error").
                key("what").value(strerror(errno)).end();
    }

    if(bsdSocket->listen(serverSocket, QUEUE_SIZE) < 0) {
        throw XmlException("server").
                key("listen").
                key("phase").value("init").
                key("status").value("error").
                key("what").value(strerror(errno)).end();
    }

    QObject::connect(this, &FTPcontroller::newConnection,
                     this, &FTPcontroller::handleConnection);

    XmlCout("server").
            key("phase").value("init").
            key("status").value("ended");
}

void FTPcontroller::setBsdSocketFactory(const InterfaceBsdSocketFactory &newFactory) {
    bsdSocket = FactoryRef(newFactory.clone());
}

void FTPcontroller::start() {
    sockaddr_in addr;
    socklen_t len;

    XmlCout("server").
            key("phase").value("waitingLoop").
            key("status").value("started");

    forever {
        int clientSocket = bsdSocket->accept(serverSocket, nullptr, nullptr);

        if(clientSocket == -1) {
            XmlCout("server").
                    key("phase").value("waitingLoop").
                    key("status").value("error").
                    key("what").value(strerror(errno));
        }

        //exceeded maximum connections limits
        if(activeClients >= MAX_CLIENTS) {
            sendMaxActiveClientMessage(clientSocket);
            bsdSocket->close(clientSocket);
        } else {
            char buff[64] = "";

            //get client ip
            getpeername(clientSocket, reinterpret_cast<sockaddr*>(&addr), &len);
            inet_ntop(addr.sin_family, &addr.sin_addr, buff, sizeof(buff));

            QString ip(buff);

            XmlCout("server").
                    key("phase").value("waitingLoop").
                    key("status").value("new connection").
                    key("socket").value(QString::number(clientSocket)).
                    key("ip").value(ip.isEmpty()? "Unknown" : ip);

            activeClients++;
            sendWelcomeMessage(clientSocket);
            createNewAccount(addr, clientSocket);
            emit newConnection(clientSocket);
        }
    }
}

void FTPcontroller::handleConnection(int clientSocket) {
    FTPconnectionWorker *worker = new FTPconnectionWorker(clientSocket);
    worker->setAutoDelete(true);

    QObject::connect(worker, &FTPconnectionWorker::done,
                     this, &FTPcontroller::cleanupConnection);

    QThreadPool::globalInstance()->start(worker);
}

void FTPcontroller::cleanupConnection(int clientSocket) {
    bsdSocket->close(clientSocket);

    QString ip;

    try{
        sockaddr_in addr = db.getAccountInfo(clientSocket).getCommandChannelAddress();
        char buff[64] = "";
        inet_ntop(addr.sin_family, &addr.sin_addr, buff, sizeof(buff));

        ip = buff;
        db.delAccountInfo(clientSocket);
    }catch(InterfaceAccountDatabase::AccountNotFoundException) {

    }

    activeClients--;

    XmlCout("server").
            key("phase").value("waitingLoop").
            key("status").value("connection closed").
            key("socket").value(QString::number(clientSocket)).
            key("ip").value(ip.isEmpty() ? "Unknown" : ip);
}

bool FTPcontroller::sendMaxActiveClientMessage(int clientSocket) {
    QByteArray array = QString("%1 %2").arg(ReplyCodes::C11.getId()).arg("Connection refused due to maximum connections limit.").toUtf8() + '\r';
    return bsdSocket->write(clientSocket, array.data(), static_cast<size_t>(array.size())) == array.size();
}

bool FTPcontroller::sendWelcomeMessage(int clientSocket) {
    QByteArray array = QString("%1 %2").arg(ReplyCodes::C220.getId()).arg("Welcome.").toUtf8() + '\r';
    return bsdSocket->write(clientSocket, array.data(), static_cast<size_t>(array.size())) == array.size();
}

void FTPcontroller::createNewAccount(const sockaddr_in &addr, int clientSocket)
{
    AccountInfo acc;
    acc.setCommandChannelAddress(addr);
    acc.setCommandChannelSocket(clientSocket);
    db.addAccountInfo(acc);
}
