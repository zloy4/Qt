#include "advanced_data_processor.h"

void AdvancedDataProcessor::toUpperCase(const QString &input)
{
    QString result = input.toUpper();
    emit textConverted(result);
}

void AdvancedDataProcessor::addPrefix(const QString &input)
{
    QString result = "Обработано: " + input;
    emit textFormatted(result);
}
