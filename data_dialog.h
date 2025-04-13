#ifndef DATA_DIALOG_H
#define DATA_DIALOG_H

#include <QDialog>

class QLineEdit;
class QComboBox;
class QPushButton;

class DataDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DataDialog(QWidget *parent = nullptr);

signals:
    void dataProcessed(const QString &result);

private slots:
    void processAndSend();

private:
    QLineEdit *inputField;
    QComboBox *modeBox;
    QPushButton *okButton;
};

#endif // DATA_DIALOG_H
