#include "chatserver.h"
#include <QDebug>

ChatServer::ChatServer(QObject *parent) : QObject(parent) {
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &ChatServer::onNewConnection);

    if (!server->listen(QHostAddress::Any, 1234)) {
        qCritical() << "Сервер не запущен:" << server->errorString();
    } else {
        qDebug() << "Сервер слушает порт 1234";
    }
}

void ChatServer::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    clients << clientSocket;
    connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void ChatServer::onReadyRead() {
    QTcpSocket *senderClient = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = senderClient->readAll();
    for (QTcpSocket *client : clients) {
        if (client != senderClient) {
            client->write(data);
        }
    }
}
