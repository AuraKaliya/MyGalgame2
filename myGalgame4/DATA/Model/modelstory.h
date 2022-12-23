#ifndef MODELSTORY_H
#define MODELSTORY_H

#include "modelbase.h"

#pragma execution_character_set("utf-8")
class ModelStory:public ModelBase
{
public:
    ModelStory();

    virtual void setValues(int,QList<QString>);
    virtual void setValues(int r,int c,QString);
    virtual QString getValues(int r,int c=0);
    virtual void addValues(int,QString);
    virtual void setGradeTableSize(int r);



private:
    /**剧情模块对应表情系统 固定 0 正常 1 开心 2 害羞 3 生气 4 惊讶 **/
    QList< QList <QString> > emotion;



};

#endif // MODELSTORY_H
