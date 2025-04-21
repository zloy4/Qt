#ifndef SPIRALPROGRESSINDICATOR_H
#define SPIRALPROGRESSINDICATOR_H

#include <QWidget>
#include <QPropertyAnimation>

class SpiralProgressIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int progress READ progress WRITE setProgress NOTIFY progressChanged)

public:
    explicit SpiralProgressIndicator(QWidget *parent = nullptr);

    int minimum() const;
    int maximum() const;
    int progress() const;

public slots:
    void setMinimum(int min);
    void setMaximum(int max);
    void setProgress(int value);

signals:
    void progressChanged(int value);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    int m_minimum;
    int m_maximum;
    int m_progress;
    QPropertyAnimation *m_animation;
};

#endif // SPIRALPROGRESSINDICATOR_H


