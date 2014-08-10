#include "hexmanager.h"

QString HexManager::toPrintableHex(QByteArray charString)
{
    return toHex(charString,kFirstPrintableChar,kLastPrintableChar);
}

QString HexManager::toAlphaNumericHex(QByteArray charString)
{
    return toHex(charString,kFirstAlphanumeric,kLastAlphanumeric);
}

QString HexManager::toHex(QByteArray charString, int ignoreRangeBegin, int ignoreRangeEnd)
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

