#include "fakeclientdataserver.h"
#include <QThread>
#include <QDebug>
#include <unistd.h>
#include <errno.h>
#pragma GCC diagnostic ignored "-Wold-style-cast"

FakeClientDataServer::FakeClientDataServer(const sockaddr_in &address, QObject *parent) : QObject(parent), server(address)
{
    server.moveToThread(&serverThread);
    QObject::connect(&serverThread, &QThread::started, &server, &Server::run);
    serverThread.start();
}

FakeClientDataServer::~FakeClientDataServer()
{
    serverThread.quit();
    serverThread.wait();
}

bool FakeClientDataServer::isServerReady() const
{
    return server.isServerReady();
}

bool FakeClientDataServer::isNewConnection() const
{
    return server.isNewConnection();
}

bool FakeClientDataServer::isError() const
{
    return server.isError();
}

QString FakeClientDataServer::getErrorMsg() const
{
    return server.getErrorMsg();
}

Server::Server(const sockaddr_in &address): address(address)
{
    serverReady = false;
    newConnection = false;
    error = false;
}

bool Server::isServerReady() const
{
    return serverReady;
}

bool Server::isNewConnection() const
{
    return  newConnection;
}

bool Server::isError() const
{
    return error;
}

QString Server::getErrorMsg() const
{
    return errorMsg;
}

void Server::run()
{
    int sk = socket(AF_INET, SOCK_STREAM, 0);
    char reuse_addr_val = 1;

    setsockopt(sk, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));

    if(bind(sk, (const sockaddr*)&address, sizeof(address))) {
        setError(QString("Error during binding: ") + strerror(errno));
        return;
    }

    if(listen(sk, 1)) {
        setError(QString("Error during listening!") + strerror(errno));
        return;
    }

    serverReady = true;
    int clientSocket = accept(sk, nullptr, nullptr);
    newConnection = true;
    close(clientSocket);
    close(sk);
}

void Server::setError(QString what)
{
    errorMsg = what;
    error = true;
}
