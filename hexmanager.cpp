#include "hexmanager.h"

QString HexManager::toPrintableHex(QByteArray charString)
{
    return toHexString(charString,kFirstPrintableChar,kLastPrintableChar);
}

QString HexManager::toAlphaNumericHex(QByteArray charString)
{
    return toHexString(charString,kFirstAlphanumeric,kLastAlphanumeric);
}

QString HexManager::toHexString(QByteArray charString, int ignoreRangeBegin, int ignoreRangeEnd)
{
    QString output;
    for(auto character:charString)
    {
        if(character >= ignoreRangeBegin && character <= ignoreRangeEnd)
            output.append(kCharPrefix + character);
        else
            output.append("[" + kHexPrefix + QString::number(character,16) + "]");
    }
    return output;
}

