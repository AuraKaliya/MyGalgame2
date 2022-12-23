#include "modellove.h"

ModelLove::ModelLove()
{

}

void ModelLove::setValues(int r, QList<QString> strl)
{
    if(linesGrade.size()>r)
    linesGrade[r]=strl;

}

void ModelLove::setValues(int r, int c, QString str)
{
    if(linesGrade.size()>r&&linesGrade[r].size()>c)
        linesGrade[r][c]=str;
}

QString ModelLove::getValues(int r, int c)
{
    return linesGrade[r][c];
}

void ModelLove::addValues(int r, QString str)
{
    linesGrade[r].push_back(str);
}

void ModelLove::setGradeTableSize(int r)
{
    linesGrade.clear();
    for( int i=0;i<r ;i++)
    {
        QList<QString> tmpList;
        linesGrade.append(tmpList);
    }
}
