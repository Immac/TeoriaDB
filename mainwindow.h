#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "logreader.h"

typedef std::shared_ptr<LogReader> LogReaderPtr;

namespace Ui {
class MainWindow;
}
namespace{
const QString kDBStatus = "Database Status: ";
const QString kSpace = " ";
const QString kDBOKStatus = "OK";
const QString kPleaseWait = "Please Wait...";
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_connect_clicked();

    void on_pbRawLog_clicked();

    void on_pbDisconnect_clicked();

    void on_pb_testQuery_clicked();

    void on_pb_clearConsole_clicked();

private:
    QString connectionStringTest = QString("Server=TEORIA-PC\\TDB;Database=TestDB;UID=sa;PWD=kanako;");
    Ui::MainWindow *ui;
    LogReaderPtr myLogReader;
    /** Helper Functions **/
    bool checkStatus();
    void connectDisable(bool disableConnect);
};

#endif // MAINWINDOW_H
