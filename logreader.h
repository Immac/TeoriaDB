#ifndef LOGREADER_H
#define LOGREADER_H
#include <QtSql>
#include <memory>

typedef std::shared_ptr<QSqlDatabase> QSqlDatabasePtr;
namespace
{
const QString kDBType = QString("QODBC");
const QString kDriver = QString("DRIVER={SQL SERVER};");
}
class LogReader
{
public:
    LogReader(): connectionString(){}
    LogReader(QString cString): connectionString(cString){}
    QSqlError getDBStatus();
private:
    QString connectionString;
    QSqlDatabasePtr database;
};

#endif // LOGREADER_H
