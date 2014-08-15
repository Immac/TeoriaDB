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
        int queryCounter = 0;
        query.exec(queryString);
        while(query.next())
        {
            queryCounter++;
            auto valString = query.value(0).toString();
            auto val = query.value(0);
            QString printableText = HexManager::toHexString(query.value(0).toByteArray());
            output.append(kQueryCount + QString::number(queryCounter) + kSpace + printableText);
            output.append(kReturn);
        }
        database->close();
        return output;
    }
    return kError;
}
