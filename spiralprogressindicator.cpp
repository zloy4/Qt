#include "spiralprogressindicator.h"
#include <QPainter>
#include <QWheelEvent>
#include <QtMath>

SpiralProgressIndicator::SpiralProgressIndicator(QWidget *parent)
    : QWidget(parent),
      m_minimum(0),
      m_maximum(100),
      m_progress(0),
      m_animation(new QPropertyAnimation(this, "progress", this))
{
    m_animation->setDuration(300);
    m_animation->setEasingCurve(QEasingCurve::InOutCubic);
}

int SpiralProgressIndicator::minimum() const { return m_minimum; }
int SpiralProgressIndicator::maximum() const { return m_maximum; }
int SpiralProgressIndicator::progress() const { return m_progress; }

void SpiralProgressIndicator::setMinimum(int min) { m_minimum = min; }
void SpiralProgressIndicator::setMaximum(int max) { m_maximum = max; }

void SpiralProgressIndicator::setProgress(int value)
{
    value = qBound(m_minimum, value, m_maximum);
    if (m_progress != value)
    {
        m_progress = value;
        emit progressChanged(m_progress);
        update();
    }
}

void SpiralProgressIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    painter.translate(width() / 2, height() / 2);

    // Спираль
    QPen pen(Qt::blue, 3);
    painter.setPen(pen);

    qreal angleStep = 7; // шаг по углу
    qreal a = 50;         // начальный радиус
    qreal b = 20;       // коэффициент роста спирали

    int totalSteps = (m_progress - m_minimum) * 360 / (m_maximum - m_minimum);

    QPointF prevPoint(0, 0);
    for (qreal angle = 0; angle <= totalSteps; angle += angleStep)
    {
        qreal rad = qDegreesToRadians(angle);
        qreal r = a + b * rad;
        QPointF point(r * qCos(rad), r * qSin(rad));

        if (angle > 0)
            painter.drawLine(prevPoint, point);

        prevPoint = point;
    }

    // Текст в центре
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);
    painter.setPen(Qt::black);
    QString text = QString::number(m_progress);
    QRectF textRect(-side / 4, -side / 4, side / 2, side / 2);
    painter.drawText(textRect, Qt::AlignCenter, text);
}

void SpiralProgressIndicator::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15;
    int newValue = m_progress + numSteps;
    m_animation->stop();
    m_animation->setStartValue(m_progress);
    m_animation->setEndValue(qBound(m_minimum, newValue, m_maximum));
    m_animation->start();
}


