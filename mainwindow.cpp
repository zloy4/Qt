#include "mainwindow.h"
#include "spiralprogressindicator.h"

#include <QVBoxLayout>
#include <QSlider>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    m_indicator = new SpiralProgressIndicator(this);
    m_indicator->setMinimum(0);
    m_indicator->setMaximum(100);
    m_indicator->setProgress(50);
    m_indicator->setMinimumSize(300, 300);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(0, 100);
    m_slider->setValue(50);

    layout->addWidget(m_indicator);
    layout->addWidget(m_slider);

    setCentralWidget(central);

    // соединение слайдера с индикатором
    connect(m_slider, &QSlider::valueChanged, m_indicator, &SpiralProgressIndicator::setProgress);
    connect(m_indicator, &SpiralProgressIndicator::progressChanged, m_slider, &QSlider::setValue);
}

MainWindow::~MainWindow() = default;



