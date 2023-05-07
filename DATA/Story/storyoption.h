#ifndef STORYOPTION_H
#define STORYOPTION_H

#include <QObject>
#include <QString>
#include <QVariant>

#include "../DATA/instruction.h"

class StoryOption : public QObject
{
    Q_OBJECT
public:
    explicit StoryOption(QObject *parent = nullptr);
    enum OptionCategory{character,player,non};

    void init(OptionCategory &category,QString &text,QString &ins_Head,QString &ins_Body);

private:

    OptionCategory m_category;
    QString m_text;
    Instruction m_ins;

signals:

};

#endif // STORYOPTION_H
