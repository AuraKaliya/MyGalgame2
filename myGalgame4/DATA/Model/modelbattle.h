#ifndef MODELBATTLE_H
#define MODELBATTLE_H

#include "modelbase.h"
#pragma execution_character_set("utf-8")
class ModelBattle:public ModelBase
{
public:
    ModelBattle();

    //这部分需要在初始化时进行设置容量

    virtual void setValues(int,QList<QString>);
    virtual void setValues(int r,int c,QString);
    virtual QString getValues(int r,int c=0);
    virtual void addValues(int,QString);
    virtual void setGradeTableSize(int r);


private:
    /**战斗模块中，等级表对应 0 数值 1 成长**/
    QList<QList < QString> > attribution;

    /*同样用一组作为备份*/
    QList<QString> attr;        //ATK DEF DHP
    QList <QString> growthAttr;


};

#endif // MODELBATTLE_H
