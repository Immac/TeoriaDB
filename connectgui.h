#ifndef CONNECTGUI_H
#define CONNECTGUI_H

#include <QDialog>

namespace Ui {
class ConnectGui;
}

class ConnectGui : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectGui(QWidget *parent = 0);
    ~ConnectGui();

    QString getServername() const;

    QString getDatabaseName() const;

    QString getUserName() const;

    QString getPassword() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ConnectGui *ui;
    QString servername,
    databaseName,
    userName,
        password;


};

#endif // CONNECTGUI_H
