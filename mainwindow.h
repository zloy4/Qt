#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Конструктор и деструктор
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слоты для обработки событий кнопок
    void addBook();
    void editBook();
    void removeBook();
    void searchBooks();  // Слот для поиска
    void importCSV();
    void exportCSV();
    void updateFilter();

private:
    // Указатели на элементы UI
    Ui::MainWindow *ui;
    QStandardItemModel *model;  // Модель данных для отображения книг
    QSortFilterProxyModel *proxyModel;  // Прокси-модель для фильтрации и сортировки

    // Вспомогательные методы для настройки модели и поиска
    void setupModel();
    void setupSearch();
};

#endif // MAINWINDOW_H



