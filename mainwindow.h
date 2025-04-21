#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SpiralProgressIndicator;
class QSlider;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    SpiralProgressIndicator *m_indicator;
    QSlider *m_slider;
};

#endif // MAINWINDOW_H



