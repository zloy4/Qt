#ifndef ADVANCED_DATA_PROCESSOR_H
#define ADVANCED_DATA_PROCESSOR_H

#include <QObject>

class AdvancedDataProcessor : public QObject {
    Q_OBJECT
public:
    explicit AdvancedDataProcessor(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void textConverted(const QString &text);
    void textFormatted(const QString &text);

public slots:
    void toUpperCase(const QString &input);
    void addPrefix(const QString &input);
};

#endif // ADVANCED_DATA_PROCESSOR_H
