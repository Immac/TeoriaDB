#ifndef REGISTERRESTORER_H
#define REGISTERRESTORER_H
#include <QDialog>
#include <QByteArray>
#include <QList>
#include <QDateTime>
#include <QGridLayout>
#include "hexmanager.h"
#include "bytecaster.h"
#include "fielddesccriptor.h"

namespace Ui {
class RegisterRestorer;
}

class RegisterRestorer : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterRestorer(QWidget *parent = 0);
    ~RegisterRestorer();
    void initialize(QByteArray input);
    QByteArray registerData;

    QByteArray nullBits;
    QByteArray columnCountByteArray;

    QByteArray fixedDataByteArray;
    QByteArray endOfFixedDataByteArray;

    QByteArray variableDataByteArray;
    QList<int> variableColumnOffsets;
    QList<FieldDescriptor*> descriptors;

    int columnCount;
    int variableColumnCount;
    int endOfData;
    const int endOfFixedDataSizePosition= 4;

    void createFieldDescriptors(double columnCount);
private slots:
    void on_pbRecover_clicked();

private:
    void updateStatusBitA();
    void updateStatusBitB();
    int updateEndOfFixedData();
    void updateFixedData(int endOfData);
    int updateColumnCount();
    void updateNullBits(double columnCount);
    int updateVariableColumnCount();
    void updateOffsets(int variableColumnCount);
    void updateVariableData();
private:
    Ui::RegisterRestorer *ui;
    int positionIndicator;
    int calculateDecimalLength(int input);
};

#endif // REGISTERRESTORER_H
