#ifndef CHARACTERINFOSHOWWIDGET_H
#define CHARACTERINFOSHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QString>
#include <QVector>
#include <QString>
#include "../DATA/Story/character.h"
#include "style.h"

class CharacterInfoShowWidget : public QWidget
{
    Q_OBJECT
public:
    static CharacterInfoShowWidget* getInstance();  // 单例方法

    void initCharacterInfomation(Character* character);
    void showLoveLines(QString st);
signals:



private:
    explicit CharacterInfoShowWidget(QWidget *parent = nullptr);
    ~CharacterInfoShowWidget();  // 析构函数

    QVBoxLayout * m_smallVLayout;
    QHBoxLayout * m_headHLayout;
    QVBoxLayout * m_mainVLayout;

    QLabel * m_headLabel;
    QLabel * m_IDLabel;
    QLabel * m_nameLabel;
    QLabel * m_nicoTitle;
    QLabel * m_splitLabel1;
    QLabel * m_splitLabel2;
    QLabel * m_splitLabel3;
    QLabel * m_introdutionLabel;
    QLabel * m_LoveInfoLabel;

    QLabel * backLabel;

    QVector<QLabel*> topLabelGroup;
    QVector<QLabel*> splitLabelGroup;

    static CharacterInfoShowWidget* m_instance;  // 单例指针
};

#endif // CHARACTERINFOSHOWWIDGET_H
