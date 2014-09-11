#include "hexmanager.h"

QString HexManager::toPrintableHex(QByteArray charString)
{
    return toHexString(charString,kFirstPrintableChar,kLastPrintableChar);
}

QString HexManager::toAlphaNumericHex(QByteArray charString)
{
    return toHexString(charString,kFirstAlphanumeric,kLastAlphanumeric);
}

QString HexManager::toHexString(QByteArray byteArray, int ignoreRangeBegin, int ignoreRangeEnd)
{
    QString output;

    for(auto byte:byteArray)
    {
        if(byte >= ignoreRangeBegin && byte <= ignoreRangeEnd)
            output.append(kCharPrefix + byte);
        else
            output.append("[" + kHexPrefix + prependZero(byte) + "]");
    }
    return output;
}

QString HexManager::prependZero(unsigned char byte)
{
    int oneDigitHexMax = 16;
    return (byte < oneDigitHexMax) ? QString("0") + QString::number(byte,16):QString::number(byte,16);
}

