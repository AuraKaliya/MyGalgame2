#include "storyoption.h"

StoryOption::StoryOption(QObject *parent) : QObject(parent)
{

}

void StoryOption::init(StoryOption::OptionCategory &category, QString &text, QString &ins_Head, QString &ins_Body)
{
    m_category=category;
    m_text=text;
    m_ins.setProperty("insObject",QVariant::fromValue(ins_Head));
    m_ins.setProperty("insDoing",QVariant::fromValue(ins_Body));
}


