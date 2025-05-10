#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), server(new ChatServer(this)), client(new ChatClient(this)) {

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);

    messageInput = new QLineEdit(this);
    sendButton = new QPushButton("Отправить", this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *inputLayout = new QHBoxLayout;

    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);

    mainLayout->addWidget(chatDisplay);
    mainLayout->addLayout(inputLayout);

    central->setLayout(mainLayout);
    resize(500, 400);
    setWindowTitle("Чат клиент-сервер");

    connect(sendButton, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(client, &ChatClient::messageReceived, this, &MainWindow::receiveMessage);
}

MainWindow::~MainWindow() {}

void MainWindow::sendMessage() {
    QString message = messageInput->text();
    if (!message.isEmpty()) {
        client->sendMessage(message);
        chatDisplay->append("[Вы]: " + message);
        messageInput->clear();
    }
}

void MainWindow::receiveMessage(const QString &msg) {
    chatDisplay->append("[Сервер]: " + msg);
}
