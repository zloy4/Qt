#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDate>
#include <QDebug>
#include <QVariant>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::processVariant);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processVariant()
{
    QString inputText = ui->inputLineEdit->text();
    QVariant var;
    bool ok = false;

    // Проверка целого
    int intValue = inputText.toInt(&ok);
    if (ok) {
        var = intValue;
    } else {
        // Проверка вещественного
        double doubleValue = inputText.toDouble(&ok);
        if (ok) {
            var = doubleValue;
        } else {
            // Проверка логического
            QString lowerText = inputText.toLower();
            if (lowerText == "true" || lowerText == "false") {
                var = (lowerText == "true");
            } else {
                // Проверка даты
                QDate dateValue = QDate::fromString(inputText, "dd.MM.yyyy");
                if (!dateValue.isValid())
                    dateValue = QDate::fromString(inputText, "dd-MM-yyyy");
                if (!dateValue.isValid())
                    dateValue = QDate::fromString(inputText, "dd/MM/yyyy");

                if (dateValue.isValid()) {
                    var = dateValue;
                } else {
                    // Строка
                    var = inputText;
                }
            }
        }
    }

    QString resultText = processAndFormatVariant(var);
    ui->resultLabel->setText(resultText);
}

QString MainWindow::processAndFormatVariant(const QVariant &var)
{
    QString result;

    switch (var.typeId()) {
    case QMetaType::Int:
        result = QString("Целое число: %1 → %2").arg(var.toInt()).arg(var.toInt() * 2);
        break;
    case QMetaType::Double:
        result = QString("Вещественное число: %1 → %2").arg(var.toDouble()).arg(QString::number(var.toDouble(), 'f', 2));
        break;
    case QMetaType::Bool:
        result = QString("Логическое: %1 → %2").arg(var.toBool() ? "true" : "false")
                  .arg(!var.toBool() ? "true" : "false");
        break;
    case QMetaType::QDate:
        result = QString("Дата: %1").arg(var.toDate().toString("dd.MM.yyyy"));
        break;
    case QMetaType::QString:
    default:
        result = QString("Строка: %1").arg(var.toString());
        break;
    }

    return result;
}
