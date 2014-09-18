#include "registerrestorer.h"
#include "ui_registerrestorer.h"

RegisterRestorer::RegisterRestorer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterRestorer)
{
    ui->setupUi(this);
}

RegisterRestorer::~RegisterRestorer()
{
    delete ui;
}


void RegisterRestorer::initialize(QByteArray input)
{
    registerData = input;
    positionIndicator = 2;
    updateStatusBitA();
    updateStatusBitB();
    endOfData = updateEndOfFixedData();
    updateFixedData(endOfData);
    columnCount = updateColumnCount();
    updateNullBits(columnCount);
    variableColumnCount =  updateVariableColumnCount();
    if (variableColumnCount > 0)
    {
        updateOffsets(variableColumnCount);
        updateVariableData();
    }
    createFieldDescriptors(columnCount);
}

void RegisterRestorer::createFieldDescriptors(double columnCount)
{
    for(int i = 0; i < columnCount ; i++)
    {
        auto newFieldDescriptor = new FieldDescriptor(ui->scrollAreaWidgetContents);
        ui->scrollAreaWidgetContents->layout()->addWidget(newFieldDescriptor);
        descriptors.append(newFieldDescriptor);
    }
    QSpacerItem *horizontalSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->scrollAreaWidgetContents->layout()->addItem(horizontalSpacer);
}

int RegisterRestorer::updateVariableColumnCount()
{
    int variableColumnCountByteCount = 2;
    QByteArray variableColumnCountByteArray;
    for(int i = 0; i < variableColumnCountByteCount; i++)
        variableColumnCountByteArray.append(registerData[positionIndicator++]);
    int varColumnCount = ByteCaster::toLongLong(variableColumnCountByteArray);
    ui->leVariableNumberOfColumns->setText(QString::number(varColumnCount));
    return varColumnCount;
}

void RegisterRestorer::updateOffsets(int variableColumnCount)
{
    QString offsetLineEditText;
    int offsetArraySize = variableColumnCount*2;
    variableColumnOffsets.append(positionIndicator + offsetArraySize);
    for(int i = 0; i < variableColumnCount; i++)
    {   QByteArray offsetsByteArray;
        int offsetByteCount = 2;
        for (int j = 0 ; j < offsetByteCount; j++)
            offsetsByteArray.append(registerData[positionIndicator++]);
        int offset = ByteCaster::toLongLong(offsetsByteArray);
        offsetLineEditText.append(QString::number(offset) + "\n");
        variableColumnOffsets.append(offset);
    }
    ui->leVariableOffsets->setText(offsetLineEditText);
}

void RegisterRestorer::updateVariableData()
{
    for(;positionIndicator < variableColumnOffsets.last();positionIndicator++)
        variableDataByteArray.append(registerData[positionIndicator]);
    ui->leVariableData->setText(HexManager::toHexString(variableDataByteArray));
}

int RegisterRestorer::calculateDecimalLength(int input)
{
    if(input > 0 && input < 10)
        return 5;
    if(input > 9 && input < 20)
        return 9;
    if(input > 19 && input < 29)
        return 13;
    if(input > 28 && input < 38)
        return 17;
    return 0;
}

int RegisterRestorer::updateColumnCount()
{
    const int bytesInColumnCount = 2;
    for(int i = 0; i < bytesInColumnCount; i++)
        columnCountByteArray.append(registerData[positionIndicator++]);
    int columnCount = ByteCaster::toLongLong(columnCountByteArray);
    ui->leTotalColumns->setText(QString::number(columnCount));
    return columnCount;
}

void RegisterRestorer::updateNullBits(double columnCount)
{
    const int bitsInByte = 8;
    int bytesForNullBits = (int)ceil(columnCount/bitsInByte);
    for(int i = 0; i < bytesForNullBits; i++)
        nullBits.append(registerData[positionIndicator++]);
    ui->leNullBits->setText(HexManager::toHexString(nullBits));
}

int RegisterRestorer::updateEndOfFixedData()
{

    for( ;positionIndicator != endOfFixedDataSizePosition;positionIndicator++)
        endOfFixedDataByteArray.append(registerData[positionIndicator]);
    int endOfFixedDataValue = ByteCaster::toLongLong(endOfFixedDataByteArray);
    ui->leFixedEndOfDataPosition->setText(QString::number(endOfFixedDataValue));
    return endOfFixedDataValue;
}

void RegisterRestorer::updateFixedData(int endOfData)
{
    for( ;positionIndicator != endOfData; positionIndicator++)
        fixedDataByteArray.append(registerData[positionIndicator]);
    ui->leFixedData->setText(HexManager::toHexString(fixedDataByteArray));
}

void RegisterRestorer::updateStatusBitA()
{
    QByteArray statusByteA;
    statusByteA.append(registerData[0]);
    ui->leStatusBitA->setText(HexManager::toHexString(statusByteA));
}

void RegisterRestorer::updateStatusBitB()
{
    QByteArray statusByteB;
    statusByteB.append(registerData[1]);
    ui->leStatusBitB->setText(HexManager::toHexString(statusByteB));
}


void RegisterRestorer::on_pbRecover_clicked()
{
    QList<QString> Values;
    QList<QString> FieldNames;
    int currentPosition = endOfFixedDataSizePosition;
    int currentOffset = 0;
    int fixedColumnsToGo = columnCount - variableColumnCount;
    int varColumnsToGo = variableColumnCount;
    for(int i = 0; i < descriptors.size(); i++)
    {
        int start;
        int length;
        int end;
        int bitCounter = 0;
        int decimalPlace;
        QByteArray myByteArray;
        int selectedElement = descriptors[i]->getSelectedElement();
        switch (selectedElement) {
        case Char:
            if(fixedColumnsToGo == 0) break;
            length = descriptors[i]->getSizeOfElement();
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(ByteCaster::toString(myByteArray));
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case VarChar:
            if(varColumnsToGo == 0) break;
            start = variableColumnOffsets[currentOffset++];
            end = variableColumnOffsets[currentOffset];
            length = end - start;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(ByteCaster::toString(myByteArray));
            --varColumnsToGo;
            break;
        case Int:
            if(fixedColumnsToGo == 0) break;
            length = 4;
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(QString::number(ByteCaster::toLongLong(myByteArray)) );
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case BigInt:
            if(fixedColumnsToGo == 0) break;
            length = 8;
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(QString::number(ByteCaster::toLongLong(myByteArray)));
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case TinyInt:
            if(fixedColumnsToGo == 0) break;
            length = 1;
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(QString::number(ByteCaster::toLongLong(myByteArray)) );
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case DateTime:
            if(fixedColumnsToGo == 0) break;
            length = 8;
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(ByteCaster::toDateTime(myByteArray));
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case SmallDateTime:
            if(fixedColumnsToGo == 0) break;
            length = 4;
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(ByteCaster::toDateTime(myByteArray));
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case DecNum:
            if(fixedColumnsToGo == 0) break;
            length = descriptors[i]->getSizeOfElement();
            length = calculateDecimalLength(length);
            decimalPlace = descriptors[i]->getDecimalPlaces();
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(ByteCaster::toNumeric(myByteArray,decimalPlace));
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case Money:
            if(fixedColumnsToGo == 0) break;
            length = descriptors[i]->getSizeOfElement();
            length = 8;
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(ByteCaster::toMoney(myByteArray));
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case Float:
            if(fixedColumnsToGo == 0) break;
            length = 8;
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(QString::number(ByteCaster::toDouble(myByteArray)) );
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case Real:
            if(fixedColumnsToGo == 0) break;
            length = 4;
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(QString::number(ByteCaster::toReal(myByteArray)) );
            currentPosition += length;
            --fixedColumnsToGo;
            break;
        case Bit:
            if(fixedColumnsToGo == 0) break;
            if(bitCounter%8 == 0)
                currentPosition++;
            //TO DO
            bitCounter++;
            --fixedColumnsToGo;
            break;
        case Binary:
            if(fixedColumnsToGo == 0) break;
            length = descriptors[i]->getSizeOfElement();
            start = currentPosition;
            myByteArray.append(registerData.mid(start,length));
            descriptors[i]->setValue(ByteCaster::toHex(myByteArray));
            currentPosition += length;
            --fixedColumnsToGo;
            break;
            break;
        default:
            break;
        }
    }
}
