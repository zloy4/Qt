#include "chatclient.h"
#include <QDebug>

ChatClient::ChatClient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    socket->connectToHost("127.0.0.1", 1234);
}

void ChatClient::sendMessage(const QString &msg) {
    socket->write(msg.toUtf8());
}

void ChatClient::onReadyRead() {
    QByteArray data = socket->readAll();
    emit messageReceived(QString::fromUtf8(data));
}
