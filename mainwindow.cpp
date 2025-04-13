#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::updateResult);
    connect(ui->modeComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updateResult);
    connect(ui->inputLineEdit, &QLineEdit::textChanged, this, &MainWindow::updateResult);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateResult()
{
    QString inputText = ui->inputLineEdit->text();
    QString result;

    switch (ui->modeComboBox->currentIndex())
    {
    case 0: // В верхний регистр
        result = inputText.toUpper();
        break;
    case 1: // В нижний регистр
        result = inputText.toLower();
        break;
    case 2: // Обратный порядок
        std::reverse(inputText.begin(), inputText.end());
        result = inputText;
        break;
    case 3: // Удалить пробелы
        result = inputText.remove(' ');
        break;
    default:
        result = inputText;
        break;
    }

    ui->resultLabel->setText(result);
}
