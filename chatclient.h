#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QTcpSocket>
#include <QObject>

class ChatClient : public QObject {
    Q_OBJECT

public:
    explicit ChatClient(QObject *parent = nullptr);
    void sendMessage(const QString &msg);

signals:
    void messageReceived(const QString &msg);

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
};

#endif // CHATCLIENT_H
