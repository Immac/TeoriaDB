#include "logreader.h"

QSqlError LogReader::connectToDataBase()
{
    database.reset(new QSqlDatabase());
    *database = QSqlDatabase::addDatabase(kDBType);
    database->setConnectOptions();
    QString fullConnectionString = kDriver + connectionString;

    database->setDatabaseName(fullConnectionString);
    if(database->open())
        database->close();
    return database->lastError();
}

QSqlError LogReader::disconnect()
{
    database->removeDatabase(kDBType);
    return database->lastError();
}
