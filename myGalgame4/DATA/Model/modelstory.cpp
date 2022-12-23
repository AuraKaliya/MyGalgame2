#include "modelstory.h"

ModelStory::ModelStory()
{

}

void ModelStory::setValues(int r, QList<QString> strl)
{
    emotion[r]=strl;
}

void ModelStory::setValues(int r, int c, QString str)
{
    emotion[r][c]=str;
}

QString ModelStory::getValues(int r, int c)
{
    return emotion[r][c];
}

void ModelStory::addValues(int r, QString str)
{
    emotion[r].append(str);
}

void ModelStory::setGradeTableSize(int r) //不允许
{
    return;
}
