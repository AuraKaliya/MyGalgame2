#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QObject>
#include <QString>

#include "Story/Character.h"

class Instruction : public QObject
{
    // 指令类型： Story Battle  |
    // 指令对象：Player Story Character:#NAME |
    // 指令行为：getMoney:200 jump:10322 loveUp:20 |


    Q_OBJECT
    Q_PROPERTY(QString insCategory READ insCategory WRITE setInsCategory NOTIFY insCategoryChanged)
    Q_PROPERTY(QString insObject READ insObject WRITE setInsObject NOTIFY insObjectChanged)
    Q_PROPERTY(QString insDoing READ insDoing WRITE setInsDoing NOTIFY insDoingChanged )

public:

    explicit Instruction(QObject *parent = nullptr);

    QString insObject() const;
    void setInsObject(const QString &object);

    QString insDoing() const;
    void setInsDoing(const QString &doing);

    QString insCategory() const;
    void setInsCategory(const QString &category);

    static void addInTable(QString,Character*);


    Instruction& operator = (const Instruction& other)
    {
        if (this != &other) {
            // 处理本类的数据成员
            m_insCategory = other.m_insCategory;
            m_insObject = other.m_insObject;
            m_insDoing = other.m_insDoing;
        }
        return *this;
    }

signals:


    void insCategoryChanged(QString newValue);
    void insObjectChanged(QString newValue);
    void insDoingChanged(QString newValue);

private:
    static QMap <QString,Character*> m_characterTable;
    QString m_insCategory;
    QString m_insObject;
    QString m_insDoing;

};

#endif // INSTRUCTION_H
