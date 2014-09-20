#include "fielddesccriptor.h"
#include "ui_fielddesccriptor.h"

FieldDescriptor::FieldDescriptor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FieldDesccriptor)
{
    ui->setupUi(this);
    ui->cbType->addItem("Char");
    ui->cbType->addItem("Varchar");
    ui->cbType->addItem("Int");
    ui->cbType->addItem("Bigint");
    ui->cbType->addItem("Tinyint");
    ui->cbType->addItem("Datetime");
    ui->cbType->addItem("Smalldatetime");
    ui->cbType->addItem("Decimal/Numeric");
    ui->cbType->addItem("Money");
    ui->cbType->addItem("Float");
    ui->cbType->addItem("Real");
    ui->cbType->addItem("Bit");
    ui->cbType->addItem("Binary");
}

FieldDescriptor::~FieldDescriptor()
{
    delete ui;
}

void FieldDescriptor::setName(QString name)
{
    ui->leFieldName->setText(name);
}

int FieldDescriptor::getSelectedType()
{
    return ui->cbType->currentIndex();
}

void FieldDescriptor::setSelectedType(QString type)
{
    QChar firstInUpper = type.at(0).toUpper();
    type.replace(0,1,firstInUpper);
    int index = ui->cbType->findText(type,Qt::MatchContains);
    ui->cbType->setCurrentIndex(index);
}

int FieldDescriptor::getSizeOfElement()
{
    return ui->sbSize->value();
}

void FieldDescriptor::setSizeOfElement(int size)
{
    ui->sbSize->setValue(size);
}

int FieldDescriptor::getDecimalPlaces()
{
    return ui->sbPrecision->value();
}

void FieldDescriptor::setPrecision(int precision)
{
    ui->sbPrecision->setValue(precision);
}

void FieldDescriptor::setValue(QString valueText)
{
    ui->leResult->setText(valueText);
}

void FieldDescriptor::on_cbType_currentIndexChanged(int index)
{
    if(index == Char || index == Binary || index == DecNum)
        ui->sbSize->setReadOnly(false);
    else
        ui->sbSize->setReadOnly(true);
    if(index == DecNum)
        ui->sbPrecision->setEnabled(true);
    else
        ui->sbPrecision->setDisabled(true);
}

