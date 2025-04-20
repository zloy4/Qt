#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editbookdialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupModel();
    setupSearch();

    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::addBook);
    connect(ui->btnEdit, &QPushButton::clicked, this, &MainWindow::editBook);
    connect(ui->btnRemove, &QPushButton::clicked, this, &MainWindow::removeBook);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchBooks);
    connect(ui->actionImportCSV, &QAction::triggered, this, &MainWindow::importCSV);
    connect(ui->actionExportCSV, &QAction::triggered, this, &MainWindow::exportCSV);
    connect(ui->actionImportJSON, &QAction::triggered, this, &MainWindow::importJSON);
    connect(ui->actionExportJSON, &QAction::triggered, this, &MainWindow::exportJSON);
    connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel()
{
    model = new QStandardItemModel(this);
    model->setColumnCount(7);
    model->setHeaderData(0, Qt::Horizontal, "Автор");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Год");
    model->setHeaderData(3, Qt::Horizontal, "Жанр");
    model->setHeaderData(4, Qt::Horizontal, "Издательство");
    model->setHeaderData(5, Qt::Horizontal, "ISBN");
    model->setHeaderData(6, Qt::Horizontal, "Страниц");

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
}

void MainWindow::setupSearch()
{
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::updateFilter);
    connect(ui->filterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateFilter);
}

void MainWindow::addBook()
{
    EditBookDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(dialog.author())
                 << new QStandardItem(dialog.title())
                 << new QStandardItem(QString::number(dialog.year()))
                 << new QStandardItem(dialog.genre())
                 << new QStandardItem(dialog.publisher())
                 << new QStandardItem(dialog.isbn())
                 << new QStandardItem(QString::number(dialog.pages()));
        model->appendRow(rowItems);
    }
}

void MainWindow::editBook()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите книгу для редактирования");
        return;
    }

    int row = proxyModel->mapToSource(index).row();

    EditBookDialog dialog(this);
    dialog.setBookData(
        model->item(row, 0)->text(),
        model->item(row, 1)->text(),
        model->item(row, 2)->text().toInt(),
        model->item(row, 3)->text(),
        model->item(row, 4)->text(),
        model->item(row, 5)->text(),
        model->item(row, 6)->text().toInt()
    );

    if (dialog.exec() == QDialog::Accepted) {
        model->setItem(row, 0, new QStandardItem(dialog.author()));
        model->setItem(row, 1, new QStandardItem(dialog.title()));
        model->setItem(row, 2, new QStandardItem(QString::number(dialog.year())));
        model->setItem(row, 3, new QStandardItem(dialog.genre()));
        model->setItem(row, 4, new QStandardItem(dialog.publisher()));
        model->setItem(row, 5, new QStandardItem(dialog.isbn()));
        model->setItem(row, 6, new QStandardItem(QString::number(dialog.pages())));
    }
}

void MainWindow::removeBook()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите книгу для удаления");
        return;
    }
    model->removeRow(proxyModel->mapToSource(index).row());
}

void MainWindow::exportCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Экспорт в CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".csv", Qt::CaseInsensitive))
        fileName += ".csv";

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
        return;
    }

    QTextStream out(&file);

    for (int row = 0; row < model->rowCount(); ++row) {
        QStringList fields;
        for (int col = 0; col < model->columnCount(); ++col) {
            QString text = model->item(row, col)->text();
            text.replace("\"", "\"\"");
            fields.append('"' + text + '"');
        }
        out << fields.join(",") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Экспорт", "Файл сохранён успешно!");
}

void MainWindow::importCSV()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Импорт CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    model->clear();
    setupModel();

    int rowCount = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() != 4)
            continue;

        QList<QStandardItem *> rowItems;
        for (QString field : fields)
            rowItems.append(new QStandardItem(field.trimmed()));

        model->appendRow(rowItems);
        rowCount++;
    }

    file.close();

    if (rowCount == 0) {
        QMessageBox::information(this, "Импорт CSV", "Файл загружен, но он пуст.");
    } else {
        QMessageBox::information(this, "Импорт CSV", "Файл успешно загружен: " + fileName);
    }
}


void MainWindow::importJSON()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Импорт JSON", "", "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isArray()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат JSON");
        return;
    }

    model->clear();
    setupModel();

    QJsonArray array = doc.array();
    for (const QJsonValue &value : array) {
        if (!value.isObject())
            continue;

        QJsonObject obj = value.toObject();
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(obj.value("author").toString())
                 << new QStandardItem(obj.value("title").toString())
                 << new QStandardItem(QString::number(obj.value("year").toInt()))
                 << new QStandardItem(obj.value("genre").toString());

        model->appendRow(rowItems);
    }

    QMessageBox::information(this, "Импорт JSON", "Файл успешно загружен.");
}

void MainWindow::exportJSON()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Экспорт JSON", "", "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;

    if (!fileName.endsWith(".json", Qt::CaseInsensitive))
        fileName += ".json";

    QJsonArray array;
    for (int row = 0; row < model->rowCount(); ++row) {
        QJsonObject obj;
        obj["author"] = model->item(row, 0)->text();
        obj["title"] = model->item(row, 1)->text();
        obj["year"] = model->item(row, 2)->text().toInt();
        obj["genre"] = model->item(row, 3)->text();
        array.append(obj);
    }

    QJsonDocument doc(array);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
        return;
    }

    file.write(doc.toJson());
    file.close();

    QMessageBox::information(this, "Экспорт JSON", "Файл сохранён успешно!");
}


void MainWindow::updateFilter()
{
    QString searchText = ui->searchLineEdit->text();
    int selectedIndex = ui->filterComboBox->currentIndex();
    int column = -1;

    if (selectedIndex > 0)
        column = selectedIndex - 1;

    proxyModel->setFilterKeyColumn(column);
    proxyModel->setFilterFixedString(searchText);
}

void MainWindow::searchBooks()
{
    QString searchText = ui->searchLineEdit->text();
    if (searchText.isEmpty()) {
        QMessageBox::information(this, "Поиск", "Введите текст для поиска.");
        return;
    }
}



