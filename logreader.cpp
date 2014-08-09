#include "logreader.h"

QSqlError LogReader::getDBStatus()
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
