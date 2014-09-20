#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "logreader.h"
#include "ui_mainwindow.h"
#include "registerrestorer.h"
#include "connectgui.h"
#include "columnstructure.h"
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

    void populateTableSelect();
private slots:
    void on_pb_connect_clicked();
    void on_pbDisconnect_clicked();
    void on_pb_clearConsole_clicked();
    void on_pb_testQuery_clicked();
    void on_btnSelectRegister_clicked();

    void on_pushButton_clicked();

private:
    QList<QByteArray> currentData;
    QList<ColumnStructure> tableStructure;
    Ui::MainWindow *ui;
    LogReaderPtr myLogReader;
    /* Helper Functions */
    bool checkStatus();
    void connectDisable(bool disableConnect);
    QString toStringRegister(int counter, QByteArray registry);
    void setConsoleText(QString consoleText);
    int resultCount = 0;
    void updateResultCounter(int newValue);
    QString getConnectionString(int &ok);
    QString getExecutionQuery();
    void updateTableStructure();
    static const constexpr char* recoveryQueryBase = "SELECT [RowLog Contents 0] FROM sys.fn_dblog(NULL,NULL) WHERE AllocUnitName = 'dbo.%1' and operation IN ('LOP_DELETE_ROWS');";
};

#endif // MAINWINDOW_H
