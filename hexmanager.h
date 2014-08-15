#ifndef HEXMANAGER_H
#define HEXMANAGER_H
#include <algorithm>
#include <stdexcept>
#include <QString>
#include <QByteArray>
namespace
{
const QString kHexPrefix = QString("0x");
const QString kCharPrefix = QString("");
const int kFirstPrintableChar = ' ';
const int kLastPrintableChar = '~';
const int kFirstAlphanumeric = '0';
const int kLastAlphanumeric =  'z';
}

class HexManager
{
public:
    static QString toPrintableHex(QByteArray charString);
    static QString toAlphaNumericHex(QByteArray charString);
    static QString toHexString(QByteArray charString,int ignoreRangeBegin = 256,int ignoreRangeEnd = 256);


private:

    HexManager() = default;

};

#endif // HEXMANAGER_H
