#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class ChatServer : public QObject {
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer *server;
    QList<QTcpSocket*> clients;
};

#endif // CHATSERVER_H
