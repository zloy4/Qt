#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    inputField = new QLineEdit(this);
    processButton = new QPushButton("Обработать", this);

    convertedLabel = new QLabel("После преобразования:", this);
    formattedLabel = new QLabel("После форматирования:", this);
    finalLabel = new QLabel("Финальный результат:", this);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(inputField);
    layout->addWidget(processButton);
    layout->addWidget(convertedLabel);
    layout->addWidget(formattedLabel);
    layout->addWidget(finalLabel);

    processor = new DataProcessor(this);
    advancedProcessor = new AdvancedDataProcessor(this);

    // цепочка сигналов-слотов
    connect(processButton, &QPushButton::clicked, this, &MainWindow::onProcessButtonClicked);
    connect(processor, &DataProcessor::dataProcessed, advancedProcessor, &AdvancedDataProcessor::toUpperCase);
    connect(advancedProcessor, &AdvancedDataProcessor::textConverted, this, &MainWindow::handleConvertedText);
    connect(advancedProcessor, &AdvancedDataProcessor::textConverted, advancedProcessor, &AdvancedDataProcessor::addPrefix);
    connect(advancedProcessor, &AdvancedDataProcessor::textFormatted, this, &MainWindow::handleFormattedText);
}

void MainWindow::onProcessButtonClicked()
{
    QString inputData = inputField->text();
    processor->processData(inputData);
}

void MainWindow::handleConvertedText(const QString &text)
{
    convertedLabel->setText("После преобразования: " + text);
}

void MainWindow::handleFormattedText(const QString &text)
{
    formattedLabel->setText("После форматирования: " + text);
    finalLabel->setText("Финальный результат: " + text);
}
