#include "data_dialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

DataDialog::DataDialog(QWidget *parent)
    : QDialog(parent)
{
    inputField = new QLineEdit(this);
    modeBox = new QComboBox(this);
    modeBox->addItem("В верхний регистр");
    modeBox->addItem("В нижний регистр");

    okButton = new QPushButton("Обработать", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(inputField);
    layout->addWidget(modeBox);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &DataDialog::processAndSend);
}

void DataDialog::processAndSend()
{
    QString text = inputField->text();
    QString result;

    if (modeBox->currentIndex() == 0)
        result = text.toUpper();
    else
        result = text.toLower();

    emit dataProcessed(result);
    close();
}
