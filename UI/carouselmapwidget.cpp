#include "carouselmapwidget.h"

CarouselMapWidget::CarouselMapWidget(QWidget *parent)
    : QWidget{parent}
{
    animationLock=false;
    m_leftBtn=new QPushButton(this);
    m_rightBtn=new QPushButton(this);
}

void CarouselMapWidget::initCarousel(QVector<JumpLabel *> lbg, QSize curSize, QSize norSize, int margin)
{
    //resize(1600,900);

    for(auto it : m_carsouseLabelGroup)
    {
        it->setVisible(false);
        delete it;
    }
    m_carsouseLabelGroup.clear();

    update();
    m_carsouseLabelGroup=lbg;
    m_currentSize=curSize;
    m_normalSize=norSize;
    m_margin=margin;
    int i=0;
    // m_currentIdx=m_carsouseLabelGroup.size()-1;
    m_currentIdx=0;
    for (auto it:m_carsouseLabelGroup)
    {
        it->setParent(this);
        if(i==m_currentIdx)
        {
            it->resize(m_currentSize);
            it->move((width()-m_currentSize.width())/2,(height()-m_currentSize.height())/2);
        }
        else
        {

            it->resize(m_normalSize);
            it->move(((width()-m_normalSize.width())/2)+(i-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2);
        }
        //qDebug()<<QPoint((width()-m_currentSize.width())/2,(height()-m_currentSize.height())/2));
        ++i;

    }

    m_carsouseLabelGroup[m_currentIdx]->raise();

initZ();


}

void CarouselMapWidget::initChangeBtn(QString btn1N, QString btn2N)
{
    m_rightBtn->setGeometry(1100,15,50,220);
    m_leftBtn->setGeometry(0,15,50,220);

    m_rightBtn->setStyleSheet("border-image:url(:/UI/RESOURCE/test_rightBtn.png);");
    m_leftBtn->setStyleSheet("border-image:url(:/UI/RESOURCE/test_leftBtn.png);");
    connect(m_rightBtn,SIGNAL(clicked()),this,SLOT(nextLabel()));
    connect(m_leftBtn,SIGNAL(clicked()),this,SLOT(preLabel()));
    initZ();
}

void CarouselMapWidget::initMask(QMap<QLabel *, QRect> mask)
{
    m_maskGroup=mask;
    for(auto it=mask.begin();it!=mask.end();it++)
    {
        it.key()->setParent(this);
        it.key()->setVisible(true);
        it.key()->setGeometry(it.value());
        it.key()->raise();
    }
}

void CarouselMapWidget::initMaskTest()
{
    QLabel* lb1=new QLabel(this);
   QRect rect1=QRect(0,0,500,900);
   lb1->setStyleSheet("border-image:url(:/UI/RESOURCE/test_Background_mask1.png);");



    QLabel * lb2=new QLabel(this);
  QRect rect2=QRect(1100,0,500,900);
  lb2->setStyleSheet("border-image:url(:/UI/RESOURCE/test_Background_mask2.png);");
    QMap<QLabel *, QRect> tmpMap;

    tmpMap.insert(lb1,rect1);
    tmpMap.insert(lb2,rect2);
    initMask(tmpMap);

}

void CarouselMapWidget::initZ()
{
    m_leftBtn->raise();
    m_rightBtn->raise();
}

void CarouselMapWidget::initTest()
{
    resize(1150,250);
    for (int count = 0; count < 10; ++count) {

        JumpLabel * lb=new JumpLabel(this);
        lb->setStyleSheet("background:rgb("+QString::number(count*10+50)+",150,"+QString::number(count*15+100)+");");
        m_carsouseLabelGroup.append(lb);

    }
    m_currentSize=QSize(450,240);
    m_normalSize=QSize(356,190);
    m_margin=20;
    int i=0;
   // m_currentIdx=m_carsouseLabelGroup.size()-1;
    m_currentIdx=0;
//    for (auto it:m_carsouseLabelGroup)
//    {
//        it->setParent(this);

//        if(i==m_currentIdx)
//        {
//            it->resize(m_currentSize);
//            it->move((width()-m_currentSize.width())/2,(height()-m_currentSize.height())/2);
//        }
//        else
//        {
//            it->resize(m_normalSize);
//            it->move(((width()-m_normalSize.width())/2)+i*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2);
//        }
//        ++i;
//    }
    for (auto it:m_carsouseLabelGroup)
    {
        it->setParent(this);
        if(i==m_currentIdx)
        {
          it->resize(m_currentSize);
          it->move((width()-m_currentSize.width())/2,(height()-m_currentSize.height())/2);
        }
         else
        {

          it->resize(m_normalSize);
        it->move(((width()-m_normalSize.width())/2)+(i-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2);
        }
        ++i;
    }

    m_carsouseLabelGroup[m_currentIdx]->raise();



    m_rightBtn->setGeometry(1100,15,50,220);
    m_leftBtn->setGeometry(0,15,50,220);

    m_rightBtn->setStyleSheet("border-image:url(:/UI/RESOURCE/test_rightBtn.png);");
    m_leftBtn->setStyleSheet("border-image:url(:/UI/RESOURCE/test_leftBtn.png);");

   // connect(m_rightBtn,&QPushButton::clicked,this,&CarouselMapWidget::nextLabel);
   // connect(m_leftBtn,&QPushButton::clicked,this,&CarouselMapWidget::preLabel);
    initZ();
}

void CarouselMapWidget::addLabel(JumpLabel *lb)
{

}

int CarouselMapWidget::getCurrentStoryID()
{
    return m_carsouseLabelGroup[m_currentIdx]->getCardID();
}

void CarouselMapWidget::preLabel()
{

    if((m_currentIdx>0)&&!animationLock)
    {
        animationLock=true;
        QParallelAnimationGroup *group=new QParallelAnimationGroup();
        --m_currentIdx;
        m_preIdx=m_currentIdx+1;
        if(m_currentIdx<0)
        {
            m_nextIdx=m_currentIdx-1;
        }else
        {
            m_nextIdx=-2;
        }


        QPropertyAnimation *animationNowSize=new QPropertyAnimation(m_carsouseLabelGroup[m_preIdx],"geometry");
        animationNowSize->setDuration(1000);
        QObject::connect(animationNowSize,&QPropertyAnimation::finished,[this](){
            qDebug()<<"hahahahahahaha";
            qDebug()<<"preSize"<<m_carsouseLabelGroup[m_preIdx]->geometry();
            update();
        });
        QObject::connect(animationNowSize,&QPropertyAnimation::valueChanged,[this](){
            update();
        });

        qDebug()<<"start:"<<m_currentSize;
        qDebug()<<"End:"<<m_normalSize;
        animationNowSize->setStartValue(m_carsouseLabelGroup[m_preIdx]->geometry());
        animationNowSize->setEndValue(QRect(((width()-m_normalSize.width())/2)+(m_preIdx-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2,m_normalSize.width(),m_normalSize.height()));
        //qDebug()<<m_carsouseLabelGroup[m_currentIdx];
        group->addAnimation(animationNowSize);





        m_carsouseLabelGroup[m_currentIdx]->raise();
        QVector<QPropertyAnimation *>animationPosList;
        int i=0;
        for (auto it:m_carsouseLabelGroup)
        {
            if(it==m_carsouseLabelGroup[m_preIdx]||it==m_carsouseLabelGroup[m_currentIdx])
            {
                ++i;
                continue;
            }
            QPropertyAnimation *animation =new QPropertyAnimation(it,"pos");
            animation->setDuration(1000);
            QObject::connect(animation,&QPropertyAnimation::finished,[=](){
                qDebug()<<"otherSize"<<m_carsouseLabelGroup[i]->geometry();
            });
            QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
                update();
            });
            QPoint targetPos=QPoint(((width()-m_normalSize.width())/2)+(i-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2);
            animation->setEndValue(targetPos);
            animationPosList<<animation;
            group->addAnimation(animation);
            ++i;
        }


        QPropertyAnimation *animationNextSize=new QPropertyAnimation(m_carsouseLabelGroup[m_currentIdx],"geometry");
        animationNextSize->setDuration(1000);
        QObject::connect(animationNextSize,&QPropertyAnimation::finished,[this](){
            qDebug()<<"nowSize"<<m_carsouseLabelGroup[m_currentIdx]->geometry();
            update();
        });
        QObject::connect(animationNextSize,&QPropertyAnimation::valueChanged,[this](){
            update();
        });


        animationNextSize->setStartValue(m_carsouseLabelGroup[m_currentIdx]->geometry());
        animationNextSize->setEndValue(QRect(((width()-m_currentSize.width())/2)+(m_currentIdx-m_currentIdx)*(m_currentSize.width()+m_margin),(height()-m_currentSize.height())/2,m_currentSize.width(),m_currentSize.height()));

        group->addAnimation(animationNextSize);

        connect(group,&QParallelAnimationGroup::finished,[this](){
            animationLock=false;
             emit nowStory(m_carsouseLabelGroup[m_currentIdx]->getCardID());
           // preLabel();
        });

        group->start(QAbstractAnimation::DeleteWhenStopped);
        initZ();
        //        for(auto it : animationPosList)
        //            it->start(QAbstractAnimation::DeleteWhenStopped);

    }
    else
    {
        return;
    }

}

void CarouselMapWidget::preLabel(int cx)
{
    if((m_currentIdx>0)&&!animationLock)
    {
        int c=cx;
        if(c<=0) {
            emit nowStory(m_carsouseLabelGroup[m_currentIdx]->getCardID());
            return;}

        animationLock=true;
        QParallelAnimationGroup *group=new QParallelAnimationGroup();
        --m_currentIdx;
        m_preIdx=m_currentIdx+1;
        if(m_currentIdx<0)
        {
            m_nextIdx=m_currentIdx-1;
        }else
        {
            m_nextIdx=-2;
        }


        QPropertyAnimation *animationNowSize=new QPropertyAnimation(m_carsouseLabelGroup[m_preIdx],"geometry");
        animationNowSize->setDuration(1000);
        QObject::connect(animationNowSize,&QPropertyAnimation::finished,[this](){
            qDebug()<<"hahahahahahaha";
            qDebug()<<"preSize"<<m_carsouseLabelGroup[m_preIdx]->geometry();
            update();
        });
        QObject::connect(animationNowSize,&QPropertyAnimation::valueChanged,[this](){
            update();
        });

        qDebug()<<"start:"<<m_currentSize;
        qDebug()<<"End:"<<m_normalSize;
        animationNowSize->setStartValue(m_carsouseLabelGroup[m_preIdx]->geometry());
        animationNowSize->setEndValue(QRect(((width()-m_normalSize.width())/2)+(m_preIdx-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2,m_normalSize.width(),m_normalSize.height()));
        //qDebug()<<m_carsouseLabelGroup[m_currentIdx];
        group->addAnimation(animationNowSize);





        m_carsouseLabelGroup[m_currentIdx]->raise();
        QVector<QPropertyAnimation *>animationPosList;
        int i=0;
        for (auto it:m_carsouseLabelGroup)
        {
            if(it==m_carsouseLabelGroup[m_preIdx]||it==m_carsouseLabelGroup[m_currentIdx])
            {
                ++i;
                continue;
            }
            QPropertyAnimation *animation =new QPropertyAnimation(it,"pos");
            animation->setDuration(1000);
            QObject::connect(animation,&QPropertyAnimation::finished,[=](){
                qDebug()<<"otherSize"<<m_carsouseLabelGroup[i]->geometry();
            });
            QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
                update();
            });
            QPoint targetPos=QPoint(((width()-m_normalSize.width())/2)+(i-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2);
            animation->setEndValue(targetPos);
            animationPosList<<animation;
            group->addAnimation(animation);
            ++i;
        }


        QPropertyAnimation *animationNextSize=new QPropertyAnimation(m_carsouseLabelGroup[m_currentIdx],"geometry");
        animationNextSize->setDuration(1000);
        QObject::connect(animationNextSize,&QPropertyAnimation::finished,[this](){
            qDebug()<<"nowSize"<<m_carsouseLabelGroup[m_currentIdx]->geometry();
            update();
        });
        QObject::connect(animationNextSize,&QPropertyAnimation::valueChanged,[this](){
            update();
        });


        animationNextSize->setStartValue(m_carsouseLabelGroup[m_currentIdx]->geometry());
        animationNextSize->setEndValue(QRect(((width()-m_currentSize.width())/2)+(m_currentIdx-m_currentIdx)*(m_currentSize.width()+m_margin),(height()-m_currentSize.height())/2,m_currentSize.width(),m_currentSize.height()));

        group->addAnimation(animationNextSize);

        connect(group,&QParallelAnimationGroup::finished,[=](){
            animationLock=false;
            preLabel(c-1);
        });

        group->start(QAbstractAnimation::DeleteWhenStopped);
        initZ();
        //        for(auto it : animationPosList)
        //            it->start(QAbstractAnimation::DeleteWhenStopped);

    }
    else
    {
        return;
    }
}

void CarouselMapWidget::nextLabel()
{
    if((m_currentIdx<m_carsouseLabelGroup.size()-1)&&!animationLock)
    {
        animationLock=true;
        QParallelAnimationGroup *group=new QParallelAnimationGroup();
        ++m_currentIdx;
        m_preIdx=m_currentIdx-1;
        if(m_currentIdx<m_carsouseLabelGroup.size()-1)
        {
            m_nextIdx=m_currentIdx+1;
        }else
        {
            m_nextIdx=-1;
        }


        QPropertyAnimation *animationNowSize=new QPropertyAnimation(m_carsouseLabelGroup[m_preIdx],"geometry");
        animationNowSize->setDuration(1000);
        QObject::connect(animationNowSize,&QPropertyAnimation::finished,[this](){
            //qDebug()<<"hahahahahahaha";
           // qDebug()<<"preSize"<<m_carsouseLabelGroup[m_preIdx]->geometry();
            update();
        });
        QObject::connect(animationNowSize,&QPropertyAnimation::valueChanged,[this](){
            update();
        });

       // qDebug()<<"start:"<<m_currentSize;
       // qDebug()<<"End:"<<m_normalSize;
        animationNowSize->setStartValue(m_carsouseLabelGroup[m_preIdx]->geometry());
        animationNowSize->setEndValue(QRect(((width()-m_normalSize.width())/2)+(m_preIdx-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2,m_normalSize.width(),m_normalSize.height()));
        //qDebug()<<m_carsouseLabelGroup[m_currentIdx];
        group->addAnimation(animationNowSize);





        m_carsouseLabelGroup[m_currentIdx]->raise();
        QVector<QPropertyAnimation *>animationPosList;
        int i=0;
        for (auto it:m_carsouseLabelGroup)
        {
            if(it==m_carsouseLabelGroup[m_preIdx]||it==m_carsouseLabelGroup[m_currentIdx])
            {
                ++i;
                continue;
            }
            QPropertyAnimation *animation =new QPropertyAnimation(it,"pos");
            animation->setDuration(1000);
            QObject::connect(animation,&QPropertyAnimation::finished,[=](){
                qDebug()<<"otherSize"<<m_carsouseLabelGroup[i]->geometry();
            });
            QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
                update();
            });
            QPoint targetPos=QPoint(((width()-m_normalSize.width())/2)+(i-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2);
            animation->setEndValue(targetPos);
            animationPosList<<animation;
            group->addAnimation(animation);
            ++i;
        }


            QPropertyAnimation *animationNextSize=new QPropertyAnimation(m_carsouseLabelGroup[m_currentIdx],"geometry");
            animationNextSize->setDuration(1000);
            QObject::connect(animationNextSize,&QPropertyAnimation::finished,[this](){
              //  qDebug()<<"nowSize"<<m_carsouseLabelGroup[m_currentIdx]->geometry();
                update();
            });
            QObject::connect(animationNextSize,&QPropertyAnimation::valueChanged,[this](){
                update();
            });


            animationNextSize->setStartValue(m_carsouseLabelGroup[m_currentIdx]->geometry());
            animationNextSize->setEndValue(QRect(((width()-m_currentSize.width())/2)+(m_currentIdx-m_currentIdx)*(m_currentSize.width()+m_margin),(height()-m_currentSize.height())/2,m_currentSize.width(),m_currentSize.height()));

            group->addAnimation(animationNextSize);

        connect(group,&QParallelAnimationGroup::finished,[this](){
            animationLock=false;
                emit nowStory(m_carsouseLabelGroup[m_currentIdx]->getCardID());
            //nextLabel();
        });

            for(auto it=m_maskGroup.begin();it!=m_maskGroup.end();it++)
        {
            it.key()->raise();
        }
        group->start(QAbstractAnimation::DeleteWhenStopped);
        initZ();
//        for(auto it : animationPosList)
//            it->start(QAbstractAnimation::DeleteWhenStopped);

    }
    else
    {
        return;
    }
}

void CarouselMapWidget::nextLabel(int cx)
{
    if((m_currentIdx<m_carsouseLabelGroup.size()-1)&&!animationLock)
    {
        int c=cx;
        if(c<=0) {
            emit nowStory(m_carsouseLabelGroup[m_currentIdx]->getCardID());
            return;
        }
        animationLock=true;
        QParallelAnimationGroup *group=new QParallelAnimationGroup();
        ++m_currentIdx;
        m_preIdx=m_currentIdx-1;
        if(m_currentIdx<m_carsouseLabelGroup.size()-1)
        {
            m_nextIdx=m_currentIdx+1;
        }else
        {
            m_nextIdx=-1;
        }


        QPropertyAnimation *animationNowSize=new QPropertyAnimation(m_carsouseLabelGroup[m_preIdx],"geometry");
        animationNowSize->setDuration(1000);
        QObject::connect(animationNowSize,&QPropertyAnimation::finished,[this](){
          //  qDebug()<<"hahahahahahaha";
          //  qDebug()<<"preSize"<<m_carsouseLabelGroup[m_preIdx]->geometry();
            update();
        });
        QObject::connect(animationNowSize,&QPropertyAnimation::valueChanged,[this](){
            update();
        });

      //  qDebug()<<"start:"<<m_currentSize;
      //  qDebug()<<"End:"<<m_normalSize;
        animationNowSize->setStartValue(m_carsouseLabelGroup[m_preIdx]->geometry());
        animationNowSize->setEndValue(QRect(((width()-m_normalSize.width())/2)+(m_preIdx-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2,m_normalSize.width(),m_normalSize.height()));
        //qDebug()<<m_carsouseLabelGroup[m_currentIdx];
        group->addAnimation(animationNowSize);





        m_carsouseLabelGroup[m_currentIdx]->raise();
        QVector<QPropertyAnimation *>animationPosList;
        int i=0;
        for (auto it:m_carsouseLabelGroup)
        {
            if(it==m_carsouseLabelGroup[m_preIdx]||it==m_carsouseLabelGroup[m_currentIdx])
            {
                ++i;
                continue;
            }
            QPropertyAnimation *animation =new QPropertyAnimation(it,"pos");
            animation->setDuration(1000);
            QObject::connect(animation,&QPropertyAnimation::finished,[=](){
                qDebug()<<"otherSize"<<m_carsouseLabelGroup[i]->geometry();
            });
            QObject::connect(animation,&QPropertyAnimation::valueChanged,[this](){
                update();
            });
            QPoint targetPos=QPoint(((width()-m_normalSize.width())/2)+(i-m_currentIdx)*(m_normalSize.width()+m_margin),(height()-m_normalSize.height())/2);
            animation->setEndValue(targetPos);
            animationPosList<<animation;
            group->addAnimation(animation);
            ++i;
        }


        QPropertyAnimation *animationNextSize=new QPropertyAnimation(m_carsouseLabelGroup[m_currentIdx],"geometry");
        animationNextSize->setDuration(1000);
        QObject::connect(animationNextSize,&QPropertyAnimation::finished,[this](){
          //  qDebug()<<"nowSize"<<m_carsouseLabelGroup[m_currentIdx]->geometry();
            update();
        });
        QObject::connect(animationNextSize,&QPropertyAnimation::valueChanged,[this](){
            update();
        });


        animationNextSize->setStartValue(m_carsouseLabelGroup[m_currentIdx]->geometry());
        animationNextSize->setEndValue(QRect(((width()-m_currentSize.width())/2)+(m_currentIdx-m_currentIdx)*(m_currentSize.width()+m_margin),(height()-m_currentSize.height())/2,m_currentSize.width(),m_currentSize.height()));

        group->addAnimation(animationNextSize);

        connect(group,&QParallelAnimationGroup::finished,[=](){
            animationLock=false;
            nextLabel(c-1);
        });

        for(auto it=m_maskGroup.begin();it!=m_maskGroup.end();it++)
        {
            it.key()->raise();
        }
        group->start(QAbstractAnimation::DeleteWhenStopped);
        initZ();
        //        for(auto it : animationPosList)
        //            it->start(QAbstractAnimation::DeleteWhenStopped);

    }
    else
    {
        return;
    }


}

void CarouselMapWidget::setCurrentStoryByLabel(JumpLabel * JL)
{
    int des=0;

    for(auto it : m_carsouseLabelGroup)
    {
        if(JL->getCardID()==it->getCardID())
        {
            break;
        }
        ++des;
    }

    if(des>=m_currentIdx)
    {
        int tmpC=des-m_currentIdx;
        nextLabel(tmpC);
    }else
    {
        int tmpC=m_currentIdx-des;
        preLabel(tmpC);
    }


}
