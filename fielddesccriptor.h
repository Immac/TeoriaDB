#ifndef FIELDDESCCRIPTOR_H
#define FIELDDESCCRIPTOR_H

#include <QWidget>

namespace Ui {
class FieldDesccriptor;
}
enum FieldTypes
{
    Char,VarChar,Int,BigInt,TinyInt,
    DateTime,SmallDateTime,DecNum,Money,
    Float,Real,Bit,Binary
};

class FieldDescriptor : public QWidget
{
    Q_OBJECT

public:

    explicit FieldDescriptor(QWidget *parent = 0);
    ~FieldDescriptor();
    void setName(QString name);
    int getSelectedType();
    void setSelectedType(QString type);
    int getSizeOfElement();
    void setSizeOfElement(int size);
    int getDecimalPlaces();
    void setPrecision(int precision);
    void setValue(QString valueText);
private slots:
    void on_cbType_currentIndexChanged(int index);


private:
    Ui::FieldDesccriptor *ui;
};

#endif // FIELDDESCCRIPTOR_H
