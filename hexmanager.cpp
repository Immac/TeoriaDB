#include "hexmanager.h"

QString HexManager::toPrintableHex(QString charString)
{
    QString output;
    for(char character:charString.toStdString())
    {
        int charInt = (int)character;
        if(charInt >= kFirstPrintableChar && charInt <= kLastPrintableChar)
            output.append(kCharPrefix + character);
        else
            output.append(kHexPrefix + charInt);
    }
    return output;
}

QString HexManager::toLegibleHex(QString charString)
{
    QString output;
    for(char character:charString.toStdString())
    {
        int charInt = (int)character;
        if(charInt >= kFirstLetter && charInt <= kLastLetter)
            output.append(kCharPrefix + character);
        else
            output.append(kHexPrefix + charInt);
    }
    return output;
}
