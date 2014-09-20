#include "logreader.h"

QSqlError LogReader::connectToDataBase()
{
    database.reset(new QSqlDatabase());
    *database = QSqlDatabase::addDatabase(kDBType);
    database->setConnectOptions();
    QString fullConnectionString = kDriver + connectionString;
    database->setDatabaseName(fullConnectionString);

    return checkStatus();
}

QSqlError LogReader::disconnect()
{
    database->removeDatabase(database->databaseName());
    return database->lastError();
}

QSqlError LogReader::checkStatus()
{
    database->open();
    database->close();
    return database->lastError();
}

QList<QByteArray> LogReader::getRawLog()
{
    return runSingleColumnQuery(kRawLogQuery);
}

QList<QByteArray> LogReader::runTestQuery()
{
    return runSingleColumnQuery(kTestQuery);
}

QList<QByteArray> LogReader::runSingleColumnQuery(QString queryString)
{
    QList<QByteArray> output;
    QSqlQuery query(*database);
    if(database->open())
    {
        int queryCounter = 0;
        query.exec(queryString);
        while(query.next())
        {
            queryCounter++;
            auto valString = query.value(0).toString();
            auto val = query.value(0);
            output.append(query.value(0).toByteArray());
        }
        database->close();
    }
    return output;
}

QList<QByteArray> LogReader::runSeveralColumnQuery(QString queryString, int columnCount)
{
    QList<QByteArray> output;
    QSqlQuery query(*database);
    if(database->open())
    {
        int queryCounter = 0;
        query.exec(queryString);
        while(query.next())
        {
            queryCounter++;
            auto valString = query.value(0).toString();
            auto val = query.value(0);
            output.append(query.value(0).toByteArray());
        }
        database->close();
    }
    return output;
}


