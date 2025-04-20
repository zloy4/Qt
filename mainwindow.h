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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void addBook();
    void editBook();
    void removeBook();
    void searchBooks();
    void importCSV();
    void exportCSV();
    void importJSON();  // <-- вот сюда!
    void exportJSON();

    void updateFilter();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;

    void setupModel();
    void setupSearch();
};

#endif // MAINWINDOW_H

