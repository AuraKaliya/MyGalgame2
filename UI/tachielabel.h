#ifndef TACHIELABEL_H
#define TACHIELABEL_H

#include <QLabel>
#include <QObject>
#include <QRect>
#include <QMouseEvent>
#include <QString>
#include <QPixmap>
#include <QMap>
#include "../DATA/Story/character.h"
#include "../DATA/Story/characterhub.h"
#include <QPropertyAnimation>
class TachieLabel : public QLabel
{
    Q_OBJECT
public:
    TachieLabel(QWidget * parent=nullptr);
    void initCharacter(Character *character,QRect rect);
    void initTouchRect(QMap<QString,QRect>touchRect);
    void changeTachie(QString tachieType);
    void setTouchLock(bool touch);
    void mousePressEvent(QMouseEvent *e)override;
    void paintEvent(QPaintEvent* e) override;
    void setAnimationAllowed(bool);

signals:
    void CharacterTouched(Character*,QString rectType);
private:
    Character * m_character;
    QMap<QString,QRect> m_touchRect;
    bool m_touchLock;
    bool m_animationLock;
    bool m_PositionStatues;
    bool m_animationAllowed;
};

#endif // TACHIELABEL_H
