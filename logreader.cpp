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

QString LogReader::getRawLog()
{
    return runQuery(kRawLogQuery);
}

QString LogReader::runTestQuery()
{
    return runQuery(kTestQuery);
}

QString LogReader::runQuery(QString queryString)
{
    QString output;
    QSqlQuery query(*database);
    if(database->open())
    {
        query.exec(queryString);
        while(query.next())
        {
            QString printableText = HexManager::toLegibleHex(query.value(0).toString());
            output.append(printableText);
            output.append(kReturn);
        }
        database->close();
        return output;
    }
    return kError;
}
