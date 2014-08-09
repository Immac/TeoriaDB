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
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_connect_clicked();

private:
    QString connectionStringTest = QString("Server=TEORIA-PC\\TDB;Database=TestDB;UID=sa;PWD=kanako;");
    Ui::MainWindow *ui;
    LogReaderPtr myLogReader;
};

#endif // MAINWINDOW_H
