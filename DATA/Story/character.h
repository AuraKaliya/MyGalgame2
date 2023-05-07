#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>



#pragma execution_character_set("utf-8")
class Character : public QObject {
    Q_OBJECT
public:
    explicit Character(QObject *parent = nullptr);

    void init(int &ID, QString &Name, QVector<QString> &gesture, QVector<QString> &lines, QString &introduction);
    void updateRelationship();

    Q_INVOKABLE  void loveUp(int value);
    Q_INVOKABLE  void loveDown(int value);

    void setGesture(QString type, QString value);
    void setRelationship(QString value);
    void setLoveValue(int value);
    void setLines(QString type, QString value);
    void setIntroduction(QString value);

    int getID() const;
    QString getName() const;
    QString getGesture(QString type) const;
    QString getRelationship() const;
    int getLoveValue() const;
    QString getLines(QString type) const;
    QString getIntroduction() const;

    //测试
    void show();

private:
    int m_ID;
    QString m_Name;
    QMap<QString, QString> m_gesture;
    QString m_relationship;
    int m_loveValue;
    QMap<QString, QString> m_lines;
    QString m_introduction;
};

#endif // CHARACTER_H
