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
    static long long toLongLong(QByteArray input);
    static QString toString(QByteArray input);
    static QString toHex(QByteArray input);
    static QString toDateTime(QByteArray input);
    static double toDouble(QByteArray input);
    static double toReal(QByteArray input);
    static QString toNumeric(QByteArray input, int decimalPlaces);
    static QString toMoney(QByteArray input);
private:
    static QString theTime(int sizeOfBytes, QByteArray input, int secondDivider);
    static bool isSmallDate(QByteArray input);
};

union LongCharU
{
    long long integer;
    char byteArray[8];
};

union DoubleCharU
{
    double number;
    char byteArray[8];
};

union RealU
{
    float number;
    char byteArray[4];
};

#endif // BYTECASTER_H
