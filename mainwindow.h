#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "data_processor.h"
#include "advanced_data_processor.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void handleFormattedText(const QString &text);
    void handleConvertedText(const QString &text);
    void onProcessButtonClicked();

private:
    QLineEdit *inputField;
    QLabel *convertedLabel;
    QLabel *formattedLabel;
    QLabel *finalLabel;
    QPushButton *processButton;

    DataProcessor *processor;
    AdvancedDataProcessor *advancedProcessor;
};

#endif // MAINWINDOW_H
