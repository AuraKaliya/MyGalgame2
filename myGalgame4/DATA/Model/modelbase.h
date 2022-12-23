#ifndef MODELBASE_H
#define MODELBASE_H

#include <QString>
#include <QList>
#include <QMap>


#pragma execution_character_set("utf-8")
class ModelBase
{
public:
    ModelBase();
    virtual ~ModelBase();

    virtual void setValues(int,QList<QString>)=0;
    virtual void setValues(int r,int c,QString)=0;
    virtual QString getValues(int r,int c=0)=0;
    virtual void addValues(int,QString)=0;
    virtual void setGradeTableSize(int r)=0;
    //virtual void registerAttribute();






    int getKeyValue() const;
    void setKeyValue(int value);


    QList<int> getGradeTable() const;

    QList<QString> getGradeNameTable() const;

protected:
    QList<int> gradeTable;                  //模块的等级表
    QList<QString> gradeNameTable;          //各等级对应名称
    int keyValue;                           //模块等级系统中的数值
    //QMap<>


};

#endif // MODELBASE_H
