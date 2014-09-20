#include "mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateTableSelect()
{
    QString query("SELECT SO.NAME FROM sys.tables SO");
    auto queryOutput = myLogReader->runSingleColumnQuery(query);
    for(auto &item:queryOutput)
        ui->cb_TableSelect->addItem(QString(item));
}

void MainWindow::on_pb_connect_clicked()
{
    ui->lbStatus->setText(kPleaseWait);
    int ok;
    QString connectionString = getConnectionString(ok);
    if (ok != 1)
    {
        //TODO: Dialog Cancelled Connection
        return;
    }
    myLogReader.reset(new LogReader(connectionString));
    myLogReader->connectToDataBase();
    checkStatus();
    populateTableSelect();
}

void MainWindow::on_pbDisconnect_clicked()
{
    myLogReader->disconnect();
    connectDisable(false);
}

bool MainWindow::checkStatus()
{
    auto DBStatus = myLogReader->checkStatus() ;
    if(DBStatus.type() != QSqlError::NoError)
    {
        ui->lbStatus->setText(kDBStatus + DBStatus.databaseText()
                              + kReturn + DBStatus.driverText());
        connectDisable(false);
        return false;
    }
    ui->lbStatus->setText(kDBStatus + kDBOKStatus);
    connectDisable(true);
    return true;
}

void MainWindow::connectDisable(bool disableConnect)
{
    ui->pb_connect->setEnabled(!disableConnect);
    ui->pbDisconnect->setEnabled(disableConnect);
    ui->pb_testQuery->setEnabled(disableConnect);
    ui->pbDisconnect->setEnabled(disableConnect);
    ui->btnSelectRegister->setEnabled(false);
}

void MainWindow::on_pb_clearConsole_clicked()
{
    ui->tbConsole->setText(QString(""));
    ui->btnSelectRegister->setEnabled(false);
}

QString MainWindow::getConnectionString(int &ok)
{
    ConnectGui connection(this);
    connection.setModal(true);
    ok = connection.exec();
    auto serverName = connection.getServername();
    auto databaseName = connection.getDatabaseName();
    auto userName = connection.getUserName();
    auto password = connection.getPassword();
    return QString("Server=%1;Database=%2;UID=%3;PWD=%4;").arg(serverName,databaseName,userName,password);
}

QString MainWindow::getExecutionQuery()
{
    QString currentTable = ui->cb_TableSelect->currentText();
    return QString(recoveryQueryBase).arg(currentTable);
}

void MainWindow::updateTableStructure()
{
    QString currentTable = ui->cb_TableSelect->currentText();
    QString queryTextA("SELECT SC.NAME AS name, ST.NAME AS type, SC.MAX_LENGTH AS size, SC.SCALE AS scale FROM "
                       "sys.objects SO INNER JOIN sys.columns SC ON SO.object_id = SC.object_id INNER JOIN "
                       "sys.types ST ON ST.system_type_id = SC.system_type_id AND ST.name != 'sysname' WHERE ");
    QString queryTextB = QString("SO.type='U' AND SO.name='%1' ORDER BY SC.object_id").arg(currentTable);
    queryTextA.append(queryTextB);
    QSqlQuery query(*(myLogReader->database));
    if(myLogReader->database->open())
    {
        tableStructure.clear();
        query.exec(queryTextA);
        while (query.next())
        {
            ColumnStructure column;
            column.name = query.value(0).toString();
            column.type = query.value(1).toString();
            column.size = query.value(2).toInt();
            auto type = column.type.toLower();
            if(type == "decimal" || type == "numeric")
                column.size *= 2;
            column.precision = query.value(3).toInt();
            tableStructure.append(column);
        }
    }
    return;
}

void MainWindow::on_pb_testQuery_clicked()
{
    updateTableStructure();
    auto query = getExecutionQuery();
    currentData = myLogReader->runSingleColumnQuery(query);
    QString consoleText;
    int counter = 0;
    for(auto &reg:currentData)
        consoleText.append(toStringRegister(++counter,reg));
    updateResultCounter(counter);
    consoleText.append(kQueryFinished + kSpace + QString::number(counter) + kSpace + kQueryFound);
    setConsoleText(consoleText);
}

QString MainWindow::toStringRegister(int counter, QByteArray registry)
{
    return kQueryCount +
            QString::number(counter) +
            kSpace +
            HexManager::toHexString(registry) +
            kReturn;
}

void MainWindow::setConsoleText(QString consoleText)
{
    ui->tbConsole->setText(consoleText);
}

void MainWindow::updateResultCounter(int newValue)
{
    resultCount = newValue;
    if (resultCount != 0)
        ui->btnSelectRegister->setEnabled(true);
    else
        ui->btnSelectRegister->setDisabled(true);
}

void MainWindow::on_btnSelectRegister_clicked()
{
    bool ok;
    int registryId =
            QInputDialog::getInt(this, tr("Query to select"),
                                 tr("Q#: "), 1, 1, resultCount, 1, &ok);
    if (!ok)
        return;
    RegisterRestorer restorer(this);
    restorer.initialize(currentData[--registryId],tableStructure);
    restorer.setModal(true);
    restorer.exec();
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
}
