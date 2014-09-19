#include "numeric.h"

QString Numeric::toString()
{
    QString output;
    if(!isPositive)
        output.append('-');
    output.append(QString::number(integer) + QString(".") + QString::number(decimal));
    return output;
}
