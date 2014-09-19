#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "logreader.h"
#include "ui_mainwindow.h"
#include "registerrestorer.h"
#include "connectgui.h"
typedef std::shared_ptr<LogReader> LogReaderPtr;

namespace Ui {
class MainWindow;
}
namespace{
const QString kDBStatus = "Database Status: ";
const QString kDBOKStatus = "OK";
const QString kDBDisconectedStatus = "Disconnected.";
const QString kPleaseWait = "Please Wait...";
const QString kQueryFinished = "Query Finished!";
const QString kQueryResults = "Results: ";
const QString kQueryFound = "results found.";
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_connect_clicked();
    void on_pbDisconnect_clicked();
    void on_pb_clearConsole_clicked();
    void on_pb_testQuery_clicked();
    void on_btnSelectRegister_clicked();

private:
    QList<QByteArray> currentData;
    Ui::MainWindow *ui;
    LogReaderPtr myLogReader;
    /* Helper Functions */
    bool checkStatus();
    void connectDisable(bool disableConnect);
    QString toStringRegister(int counter, QByteArray registry);
    void setConsoleText(QString consoleText);
    int resultCount = 0;
    void updateResultCounter(int newValue);
    QString getQueryString(int &ok);
};

#endif // MAINWINDOW_H
