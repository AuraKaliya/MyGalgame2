#include "modelbattle.h"

ModelBattle::ModelBattle()
{
    attribution.clear();
    for(int i=0;i<2;i++)        //attr\growth
    {
        QList<QString> tmpStrl;
        for(int j=0;j<3;j++)    //atk\def\dhp
        {
            QString tmpStr="";
            tmpStrl<<tmpStr;
        }
        attribution<<tmpStrl;
    }

}

void ModelBattle::setValues(int r, QList<QString> strl)
{
    attribution[r]=strl;
}

void ModelBattle::setValues(int r, int c, QString str)
{
    attribution[r][c]=str;
}

QString ModelBattle::getValues(int r, int c)
{
    return  attribution[r][c];
}

void ModelBattle::addValues(int, QString)//这个不允许启用
{

}

void ModelBattle::setGradeTableSize(int r)      //这个不允许启用
{
    return;
}
