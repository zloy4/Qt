#include "mainwindow.h"
#include "data_dialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    openDialogButton = new QPushButton("Открыть диалог", this);
    resultLabel = new QLabel("Результат:", this);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(openDialogButton);
    layout->addWidget(resultLabel);

    dialog = new DataDialog(this);

    connect(openDialogButton, &QPushButton::clicked, this, &MainWindow::openDialog);
    connect(dialog, &DataDialog::dataProcessed, this, &MainWindow::handleProcessedData);
}

void MainWindow::openDialog()
{
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void MainWindow::handleProcessedData(const QString &result)
{
    resultLabel->setText("Результат: " + result);
}
