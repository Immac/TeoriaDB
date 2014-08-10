#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    myLogReader.reset(new LogReader(ui->leConnectionString->text()));
    myLogReader->connectToDataBase();
    checkStatus();
}

void MainWindow::on_pbRawLog_clicked()
{
    auto rawLogText =  myLogReader->getRawLog();
    ui->tbConsole->setText(rawLogText);
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
    ui->pbRawLog->setEnabled(disableConnect);
    ui->pb_testQuery->setEnabled(disableConnect);
    ui->pbDisconnect->setEnabled(disableConnect);
}

void MainWindow::on_pb_testQuery_clicked()
{
    auto textToDisplay = myLogReader->runTestQuery();
    ui->tbConsole->setText(textToDisplay);
}

void MainWindow::on_pb_clearConsole_clicked()
{
    ui->tbConsole->setText(QString(""));
}

void MainWindow::on_pb_theDebugButton_clicked()
{
    //QString string = QString("hello \x10 \x20 \x7b \x53 \x7e");
    //ui->tbConsole->setText(HexManager::toAlphaNumericHex(string));
}
