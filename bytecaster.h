#ifndef BYTECASTER_H
#define BYTECASTER_H
#include <QByteArray>
#include <QString>
#include <QDateTime>
#include "hexmanager.h"
#include "numeric.h"

class ByteCaster
{
public:
    ByteCaster() = default;
    static long long getLongFromByteArray(QByteArray input);
    static QString getStringFromByteArray(QByteArray input);
    static QString getHexFromByteArray(QByteArray input);
    static QString getTimeFromByteArray(QByteArray input);
    static double getDoubleFromByteArray(QByteArray input);
    static double getRealFromByteArray(QByteArray input);
    static QString getNumericFromByteArray(QByteArray input, int decimalPlaces);
    static QString theTime(int sizeOfBytes, QByteArray input, int secondDivider);
    static QString getMoneyFromByteArray(QByteArray input);
};

union LongCharU
{
    long long integer;
    char byteArray[sizeof(long long)];
};

union DoubleCharU
{
    double number;
    char byteArray[sizeof(long long)];
};

union RealU
{
    float number;
    char byteArray[4];
};

#endif // BYTECASTER_H
