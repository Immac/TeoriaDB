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
    ui->pb_connect->setEnabled(false);
    myLogReader.reset(new LogReader(ui->leConnectionString->text()));
    StatusCheck();
}

void MainWindow::on_pbRawLog_clicked()
{
    // TODO
}

void MainWindow::on_pbDisconnect_clicked()
{
    myLogReader->disconnect();
    StatusCheck();
}

void MainWindow::StatusCheck()
{
    auto DBStatus = myLogReader->connectToDataBase() ;
    if(DBStatus.type() != QSqlError::NoError)
        ui->lbStatus->setText(kDBStatus + DBStatus.databaseText()
                              + kReturn + DBStatus.driverText());
    else
        ui->lbStatus->setText(kDBStatus + kDBOKStatus);
}
