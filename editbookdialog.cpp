#include "editbookdialog.h"
#include "ui_editbookdialog.h"
#include <QMessageBox>

EditBookDialog::EditBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBookDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditBookDialog::validateInputs);
}

EditBookDialog::~EditBookDialog()
{
    delete ui;
}

void EditBookDialog::setBookData(const QString &author, const QString &title, int year, const QString &genre,
                                 const QString &publisher, const QString &isbn, int pages)
{
    ui->authorLineEdit->setText(author);
    ui->titleLineEdit->setText(title);
    ui->yearSpinBox->setValue(year);
    ui->genreLineEdit->setText(genre);
    ui->publisherLineEdit->setText(publisher);
    ui->isbnLineEdit->setText(isbn);
    ui->pagesSpinBox->setValue(pages);
}

QString EditBookDialog::author() const { return ui->authorLineEdit->text(); }
QString EditBookDialog::title() const { return ui->titleLineEdit->text(); }
int EditBookDialog::year() const { return ui->yearSpinBox->value(); }
QString EditBookDialog::genre() const { return ui->genreLineEdit->text(); }
QString EditBookDialog::publisher() const { return ui->publisherLineEdit->text(); }
QString EditBookDialog::isbn() const { return ui->isbnLineEdit->text(); }
int EditBookDialog::pages() const { return ui->pagesSpinBox->value(); }

void EditBookDialog::validateInputs()
{
    if (author().isEmpty() || title().isEmpty() || genre().isEmpty() ||
        publisher().isEmpty() || isbn().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все текстовые поля должны быть заполнены.");
        return;
    }
    accept();
}



