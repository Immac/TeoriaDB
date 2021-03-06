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
const QString kRawLogQuery = QString("SELECT [RowLog Contents 0] from fn_dblog(null, null) ");
const QString kTestQuery = QString("SELECT * from TestTable");
const QString kReturn = QString("\n");
const QString kError = QString("Error");
const QString kSpace = " ";
}
class LogReader
{
public:
    LogReader(): connectionString(){}
    LogReader(QString connectionString): connectionString(connectionString){}
    QSqlError connectToDataBase();
    QSqlError disconnect();
    QSqlError checkStatus();

    QList<QByteArray> getRawLog();
    QList<QByteArray> runTestQuery();
    QList<QByteArray> runSingleColumnQuery(QString queryString);
    QList<QByteArray> runSeveralColumnQuery(QString queryString,int columnCount);

    QSqlDatabasePtr database;

private:
    QString connectionString;

};

#endif // LOGREADER_H
