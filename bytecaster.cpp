#include "bytecaster.h"

long long ByteCaster::toLongLong(QByteArray input)
{
    LongCharU output;
    output.integer = 0;
    for(int i = 0; i < input.size();i++)
        output.byteArray[i] = input[i];
    return output.integer;
}

QString ByteCaster::toString(QByteArray input)
{
    QString output(HexManager::toPrintableHex(input));
    return output;
}

QString ByteCaster::toHex(QByteArray input)
{
    QString output(HexManager::toHexString(input));
    return output;
}

QString ByteCaster::theTime(int sizeOfBytes, QByteArray input, int secondDivider)
{
    QByteArray timeBytes;
    QByteArray dateBytes;
    timeBytes.append(input.left(sizeOfBytes));
    dateBytes.append(input.right(sizeOfBytes));
    long long secondFractions,daysElapsed;
    secondFractions = toLongLong(timeBytes);
    daysElapsed = toLongLong(dateBytes);
    int seconds,minutes,hours;
    int secondsElapsed,minutesElapsed,hoursElapsed;
    secondsElapsed = floor(secondFractions/secondDivider);
    minutesElapsed = floor(secondsElapsed/secInMin);
    hoursElapsed = floor(minutesElapsed/minInHr);
    seconds = secondsElapsed%secInMin;
    minutes = minutesElapsed%minInHr;
    hours = hoursElapsed%hrInDay;
    QDate date;
    date.setDate(1900,1,1);
    date = date.addDays(daysElapsed);
    QString output = date.toString() + " " + QString::number(hours) + ":" + QString::number(minutes)+ ":" +QString::number(seconds);

    return output;
}

QString ByteCaster::toMoney(QByteArray input)
{
    double output = toLongLong(input);
    return QString::number(output/10000);
}

bool ByteCaster::isSmallDate(QByteArray input)
{
    return input.size() == 4;
}

QString ByteCaster::toDateTime(QByteArray input)
{
    int sizeOfBytes = 4;
    int secondDivider = 300;
    if (isSmallDate(input))
    {
        sizeOfBytes = 2;
        secondDivider = 1;
    }
    return theTime(sizeOfBytes, input, secondDivider);
}

double ByteCaster::toDouble(QByteArray input)
{
    DoubleCharU output;
    output.number = 0;
    for(int i = 0; i < input.size(); i++ )
        output.byteArray[i] = input[i];
    return output.number;
}

double ByteCaster::toReal(QByteArray input)
{
    RealU output;
    output.number = 0;
    for(int i = 0; i < input.size(); i++ )
        output.byteArray[i] = input[i];
    return output.number;
}

QString ByteCaster::toNumeric(QByteArray input,int decimalPlaces)
{
    unsigned int position = 0;
    bool isPositive = input[position++] != '\0';
    double output = toLongLong(input.mid(1));
    for(int i = 0; i < decimalPlaces;i++)
        output /= 10;
    if(!isPositive)
        output *= -1;
    return QString::number(output);
}
