#include "Character.h"
#include <QDebug>

Character::Character(QObject *parent) : QObject(parent),
    m_ID(0), m_Name(""), m_gesture(), m_relationship(""), m_loveValue(0), m_lines(), m_introduction("")
{

}

void Character::init(int &ID, QString &Name, QVector<QString> &gesture, QVector<QString> &lines,QString &introduction)
{
    m_ID = ID;
    m_Name = Name;

    // 按照顺序添加手势和台词
    QStringList gestureKey = {"正常", "开心", "害羞", "沮丧"};
    for (int i = 0; i < gesture.size() && i < gestureKey.size(); ++i) {
        m_gesture[gestureKey[i]] = gesture[i];
    }

    QStringList linesKey = {"仇视", "陌生", "友好", "信赖", "爱恋"};
    for (int i = 0; i < lines.size() && i < linesKey.size(); ++i) {
        m_lines[linesKey[i]] = lines[i];
    }

    m_introduction = introduction;

    m_relationship = "陌生";
    m_loveValue = 0;
}

void Character::updateRelationship()
{
    //小于-10:仇视 -9~10：陌生 11-40：友好 41-70：信赖  大于71：爱恋
        if (m_loveValue < 20) {
            m_relationship = "仇视";
        } else if (m_loveValue < 40) {
            m_relationship = "陌生";
        } else if (m_loveValue < 60) {
            m_relationship = "友好";
        } else if (m_loveValue < 80) {
            m_relationship = "信赖";
        } else {
            m_relationship = "爱恋";
        }
}

void Character::loveUp(int value)
{
    m_loveValue+=value;
    updateRelationship();
}

void Character::loveDown(int value)
{
    m_loveValue-=value;
    updateRelationship();
}


void Character::setGesture(QString type, QString value)
{
    m_gesture[type] = value;
}

void Character::setRelationship(QString value)
{
    m_relationship = value;
}

void Character::setLoveValue(int value)
{
    m_loveValue = value;
}

void Character::setLines(QString type, QString value)
{
    m_lines[type] = value;
}

void Character::setIntroduction(QString value)
{
    m_introduction = value;
}

int Character::getID() const
{
    return m_ID;
}

QString Character::getName() const
{
    return m_Name;
}

QString Character::getGesture(QString type) const
{
    return m_gesture[type];
}

QString Character::getRelationship() const
{
    return m_relationship;
}

int Character::getLoveValue() const
{
    return m_loveValue;
}

QString Character::getLines(QString type) const
{
    return m_lines[type];
}

QString Character::getIntroduction() const
{
    return m_introduction;
}

void Character::show()
{
qDebug() << "ID: " << m_ID;
qDebug() << "Name: " << m_Name;
qDebug() << "Gesture:";
for (auto iter = m_gesture.begin(); iter != m_gesture.end(); ++iter) {
qDebug() << iter.key() << ": " << iter.value();
}
qDebug() << "Relationship: " << m_relationship;
qDebug() << "Love Value: " << m_loveValue;
qDebug() << "Lines:";
for (auto iter = m_lines.begin(); iter != m_lines.end(); ++iter) {
qDebug() << iter.key() << ": " << iter.value();
}
qDebug() << "Introduction: " << m_introduction;
}
