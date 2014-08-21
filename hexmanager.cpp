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
            output.append("[" + kHexPrefix + QString::number(byte,16) + "]");
    }
    return output;
}

