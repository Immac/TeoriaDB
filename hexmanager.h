#ifndef HEXMANAGER_H
#define HEXMANAGER_H
#include <algorithm>
#include <stdexcept>
#include <QString>

namespace
{
const QString kHexPrefix = QString("0x");
const QString kCharPrefix = QString("");
const int kFirstPrintableChar = 32;
const int kLastPrintableChar = 126;
const int kFirstLetter = 'a';
const int kLastLetter =  'z';
}

class HexManager
{
public:
    static QString toPrintableHex(QString charString);
    static QString toLegibleHex(QString charString);

private:
    HexManager() = default;

};

#endif // HEXMANAGER_H
