#include "connectgui.h"
#include "ui_connectgui.h"

ConnectGui::ConnectGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectGui)
{
    this->setWindowTitle(QString("Database Connection"));
    ui->setupUi(this);
}

ConnectGui::~ConnectGui()
{
    delete ui;
}

QString ConnectGui::getPassword() const
{
    return password;
}

QString ConnectGui::getUserName() const
{
    return userName;
}

QString ConnectGui::getDatabaseName() const
{
    return databaseName;
}

QString ConnectGui::getServername() const
{
    return servername;
}

void ConnectGui::on_buttonBox_accepted()
{
    servername = ui->le_Server->text();
    databaseName = ui->le_Database->text();
    userName = ui->le_Username->text();
    password = ui->le_Password->text();
}
