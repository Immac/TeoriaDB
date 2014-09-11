#ifndef NUMERIC_H
#define NUMERIC_H
#include <QString>
class Numeric
{
public:
    Numeric(bool isPositive,double integer,double decimal):
        isPositive(isPositive),integer(integer),decimal(decimal)
        {}
    QString toString();
private:
    bool isPositive;
    double integer;
    double decimal;
};

#endif // NUMERIC_H
