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
    ui->cbType->addItem("BigInt");
    ui->cbType->addItem("TinyInt");
    ui->cbType->addItem("DateTime");
    ui->cbType->addItem("SmallDateTime");
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

int FieldDescriptor::getSelectedElement()
{
    return ui->cbType->currentIndex();
}

int FieldDescriptor::getSizeOfElement()
{
    return ui->sbValue->value();
}

int FieldDescriptor::getDecimalPlaces()
{
    return ui->sbValue2->value();
}

void FieldDescriptor::setValue(QString valueText)
{
    ui->leResult->setText(valueText);
}

void FieldDescriptor::on_cbType_currentIndexChanged(int index)
{
    if(index == Char || index == Binary || index == DecNum)
        ui->sbValue->setEnabled(true);
    else
        ui->sbValue->setDisabled(true);

    if(index == DecNum)
        ui->sbValue2->setEnabled(true);
    else
        ui->sbValue2->setDisabled(true);
}

