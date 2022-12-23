#ifndef MODELGESTURE_H
#define MODELGESTURE_H

#include "modelbase.h"
#pragma execution_character_set("utf-8")
class ModelGesture:public ModelBase
{
public:
    ModelGesture();

    //需要初始化设置5个姿态



    virtual void setValues(int,QList<QString>);
    virtual void setValues(int r,int c,QString);
    virtual QString getValues(int r,int c=0);
    virtual void addValues(int,QString);
    virtual void setGradeTableSize(int r);

private:
    /**这里等级系统固定对应0 stand 1 atk 2 def 3 win 4 lose**/
    QList<QList <QString > > gesture;

};

#endif // MODELGESTURE_H
