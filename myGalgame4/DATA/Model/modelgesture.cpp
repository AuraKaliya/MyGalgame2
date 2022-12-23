#include "modelgesture.h"

ModelGesture::ModelGesture()
{
    for(int i=0;i<5;i++)
    {
        QList<QString> tmpStrl;
        gesture<<tmpStrl;
    }
}

void ModelGesture::setValues(int r, QList<QString> strl)
{
 gesture[r]=strl;
}

void ModelGesture::setValues(int r, int c, QString str)
{
    gesture[r][c]=str;
}

QString ModelGesture::getValues(int r, int c)
{
    return  gesture[r][c];
}

void ModelGesture::addValues(int r, QString str)
{
    gesture[r].append(str);
}

void ModelGesture::setGradeTableSize(int r)     //不需要
{
    return;
}
