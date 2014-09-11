#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
/*
 *   long timeInLongForm;
    time_t dateTime = static_cast<time_t>(timeInLongForm);

    hello = dateTime;

    int sizeOfField = 10;
    QByteArray myByteArray;

    char myChar[sizeOfField];

    for (int i = 0; i < sizeOfField; ++i) {
        myChar[i] = myByteArray[i];
    }


char byteArray[4];


integer myUnion;
for (int i = 0; i < 4; ++i) {
    myUnion.myChar[i] = byteArray[i];
}

int myInt = myUnion.myInt;
    union integer{
        int myInt;
        char myChar[4];
    };

*/
