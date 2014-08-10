#ifndef LOGREADER_H
#define LOGREADER_H
#include <QtSql>
#include <memory>
#include <hexmanager.h>
typedef std::shared_ptr<QSqlDatabase> QSqlDatabasePtr;
namespace
{
const QString kQueryCount = QString("Q# ");
const QString kDBType = QString("QODBC");
const QString kDriver = QString("DRIVER={SQL SERVER};");
const QString kRawLogQuery = QString("SELECT [RowLog Contents 0] from fn_dblog(null, null)");
const QString kTestQuery = QString("SELECT * from TestTable");
const QString kReturn = QString("\n");
const QString kError = QString("Error");
const QString kSpace = " ";
}
class LogReader
{
public:
    LogReader(): connectionString(){}
    LogReader(QString cString): connectionString(cString){}
    QSqlError connectToDataBase();
    QSqlError disconnect();
    QSqlError checkStatus();

    QString getRawLog();
    QString runTestQuery();

private:
    QString connectionString;
    QSqlDatabasePtr database;
    QString runQuery(QString queryString);
};

#endif // LOGREADER_H
