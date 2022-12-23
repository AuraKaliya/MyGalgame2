#include "modelbase.h"

ModelBase::ModelBase()
{

}

ModelBase::~ModelBase()
{

}



int ModelBase::getKeyValue() const
{
    return keyValue;
}

void ModelBase::setKeyValue(int value)
{
    keyValue = value;
}

QList<int> ModelBase::getGradeTable() const
{
    return gradeTable;
}

QList<QString> ModelBase::getGradeNameTable() const
{
    return gradeNameTable;
}

