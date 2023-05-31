#include "tachielabel.h"

TachieLabel::TachieLabel(QWidget * parent):QLabel(parent)
{

}

void TachieLabel::initCharacter(Character *character, QRect rect)
{
    qDebug()<<character;
    m_character=character;
    setMask(QPixmap(m_character->mask()).mask());
    //setPixmap(QPixmap(m_character->getGesture("正常")).scaled(this->size()));
    setStyleSheet("border-image:url("+m_character->getGesture(QString("正常"))+");");
    qDebug()<<pixmap()<<"============";
    setGeometry(rect);
    m_animationLock=false;
    m_PositionStatues=false;
    m_animationAllowed=true;
}

void TachieLabel::initTouchRect(QMap<QString, QRect> touchRect)
{
    m_touchRect=touchRect;
}

void TachieLabel::setGesture(QString gesturePixUrl)
{
    setStyleSheet("border-image:url("+gesturePixUrl+");");
}

void TachieLabel::changeTachie(QString tachieType)
{
    //qDebug()<<"haiweiqweiqweojqesadasd"<<m_character->getGesture(tachieType);
   // setPixmap(QPixmap(m_character->getGesture(tachieType)));
    setStyleSheet("border-image:url("+m_character->getGesture(tachieType)+");");
    update();
}

void TachieLabel::setTouchLock(bool touch)
{
    m_touchLock=touch;
}

void TachieLabel::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
         QPoint point = e->pos();

        if(m_touchLock)
        for(auto it =m_touchRect.begin();it!=m_touchRect.end();++it)
        {
             if(it.value().contains(point))
            {
                //qDebug()<<"dianjile!!!"<<it.value();
                //qDebug()<<this->pixmap();
                // qDebug()<<it.key();
                //qDebug()<<this->geometry();
                changeTachie(it.key());
                emit CharacterTouched(m_character,it.key());
                break;
            }
        }
    }

}

void TachieLabel::paintEvent(QPaintEvent *e)
{
    int height=25;
    if(m_animationAllowed)
    {
        if(m_animationLock)
    {
    }
    else
    {
        qDebug()<<"chufa!!!!";
        m_animationLock=true;
        if(m_PositionStatues)
        {
            //  下
        QPropertyAnimation * animation =new QPropertyAnimation(this,"pos");
        animation ->setDuration(1000);
        QPoint targetPos=QPoint(this->x(),this->y()+height);
        animation->setEndValue(targetPos);
        qDebug()<<"xia!!!!";
        QObject::connect(animation,&QPropertyAnimation::finished,[this](){

            m_animationLock=false;
            m_PositionStatues=false;
            qDebug()<<"xia wan!!!!";
            update();
        });

        animation->start(QAbstractAnimation::DeleteWhenStopped);
        }else
        {
            // 上
        qDebug()<<"shang!!!!";
        QPropertyAnimation * animation =new QPropertyAnimation(this,"pos");
        animation ->setDuration(1000);
        QPoint targetPos=QPoint(this->x(),this->y()-25);
        animation->setEndValue(targetPos);

        QObject::connect(animation,&QPropertyAnimation::finished,[this](){

            m_animationLock=false;
            m_PositionStatues=true;
            update();
        });

        animation->start(QAbstractAnimation::DeleteWhenStopped);

        }
    }
    }




}

void TachieLabel::setAnimationAllowed(bool al)
{
    m_animationAllowed=al;
}
