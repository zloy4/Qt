#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QLabel;
class DataDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openDialog();
    void handleProcessedData(const QString &result);

private:
    QPushButton *openDialogButton;
    QLabel *resultLabel;
    DataDialog *dialog;
};

#endif // MAINWINDOW_H
