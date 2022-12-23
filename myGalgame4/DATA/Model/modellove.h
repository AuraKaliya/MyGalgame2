#ifndef MODELLOVE_H
#define MODELLOVE_H

#include "modelbase.h"
#pragma execution_character_set("utf-8")
class ModelLove:public ModelBase

{
public:
    ModelLove();

    virtual void setValues(int,QList<QString>);     //按模块的等级表阶段添加属性/修改属性
    virtual void setValues(int r,int c,QString);
    virtual QString getValues(int r,int c=0);        //从map查找、获取某一具体属性
    virtual void addValues(int,QString);            //为某个属性添加内容
    virtual void setGradeTableSize(int r) ;

private:
    /**特化属性--台词：用于触发触摸事件时显示的台词**/
    QList<QList< QString> > linesGrade;

    /**在设计时候考虑到微调特性，设置一个备份区**/  /*但是好像没啥用*/
    QList<QString> linesGrade1;
    QList<QString> linesGrade2;
    QList<QString> linesGrade3;
    QList<QString> linesGrade4;

};

#endif // MODELLOVE_H
