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

void MainWindow::on_pb_connect_clicked()
{
    ui->lbStatus->setText(kPleaseWait);
    int ok;
    QString connectionString = getQueryString(ok);
    if (ok != 1)
    {
        //TODO: Dialog Cancelled Connection
        return;
    }
    myLogReader.reset(new LogReader(connectionString));
    myLogReader->connectToDataBase();
    checkStatus();
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

QString MainWindow::getQueryString(int &ok)
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

void MainWindow::on_pb_testQuery_clicked()
{
    auto query = ui->le_Query->text();
    currentData = myLogReader->runQuery(query);
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
    restorer.initialize(currentData[--registryId]);
    restorer.setModal(true);
    restorer.exec();
}
