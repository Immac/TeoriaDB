#include "bytecaster.h"


long long ByteCaster::getLongFromByteArray(QByteArray input)
{
    LongCharU output;
    output.integer = 0;
    for(int i = 0; i < input.size();i++)
        output.byteArray[i] = input[i];
    return output.integer;
}

QString ByteCaster::getStringFromByteArray(QByteArray input)
{
    QString output(HexManager::toPrintableHex(input));
    return output;
}

QString ByteCaster::getHexFromByteArray(QByteArray input)
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
    secondFractions = getLongFromByteArray(timeBytes);
    daysElapsed = getLongFromByteArray(dateBytes);
    int seconds,minutes,hours;
    int secondsElapsed,minutesElapsed,hoursElapsed;
    secondsElapsed = floor(secondFractions/secondDivider);
    minutesElapsed = floor(secondsElapsed/60);
    hoursElapsed = floor(minutesElapsed/60);
    seconds = secondsElapsed%60;
    minutes = minutesElapsed%60;
    hours = hoursElapsed%24;
    QDate date;
    date.setDate(1900,1,1);
    date = date.addDays(daysElapsed);
    QString output = date.toString() + " " + QString::number(hours) + ":" + QString::number(minutes)+ ":" +QString::number(seconds);

    return output;
}

QString ByteCaster::getMoneyFromByteArray(QByteArray input)
{
    double output = getLongFromByteArray(input);
    return QString::number(output/10000);
}

QString ByteCaster::getTimeFromByteArray(QByteArray input)
{
    int sizeOfBytes = 2;
    int secondDivider = 1;
    if (input.size() == 8)
    {
        sizeOfBytes = 4;
        secondDivider = 300;
    }
    return theTime(sizeOfBytes, input, secondDivider);
}

double ByteCaster::getDoubleFromByteArray(QByteArray input)
{
    DoubleCharU output;
    output.number = 0;
    for(int i = 0; i < input.size(); i++ )
        output.byteArray[i] = input[i];
    return output.number;
}

double ByteCaster::getRealFromByteArray(QByteArray input)
{
    RealU output;
    output.number = 0;
    for(int i = 0; i < input.size(); i++ )
        output.byteArray[i] = input[i];
    return output.number;
}

QString ByteCaster::getNumericFromByteArray(QByteArray input,int decimalPlaces)
{
    unsigned int position = 0;
    bool isPositive = input[position++] != '\0';
    double output = getLongFromByteArray(input.mid(1));
    for(int i = 0; i < decimalPlaces;i++)
        output /= 10;
    if(!isPositive)
        output *= -1;
    return QString::number(output);
}
