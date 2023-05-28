#include "chievementwidget.h"

chievementWidget::chievementWidget(QWidget *parent)
    : QWidget{parent}
{
    m_centerLabel = new QLabel(this);
    m_readLabel = new JumpLabel(this);
    m_saveLabel = new JumpLabel(this);


    m_achInfoLaebl = new QLabel(this);
    m_emblemLabel1 = new QLabel(this);
    m_emblemLabel2 = new QLabel(this);
    m_emblemLabel3 = new QLabel(this);
    m_emblems.push_back(m_emblemLabel1);
    m_emblems.push_back(m_emblemLabel2);
    m_emblems.push_back(m_emblemLabel3);

    m_achIDLabel = new QLabel(this);
    m_storyProgressLabel = new QLabel(this);
    m_gameLevelLabel = new QLabel(this);
    m_infoLabels.push_back(m_achIDLabel);
    m_infoLabels.push_back(m_storyProgressLabel);
    m_infoLabels.push_back(m_gameLevelLabel);

    setFixedSize(900,200);




}

void chievementWidget::initRSLabel(QString readNormal, QString readPress, QString saveNormal, QString savePress)
{


    m_readLabel->setPixmapPathGroup(readNormal,readPress);

    m_readLabel->setPixmapGroup(new QPixmap(readNormal),new QPixmap(readPress));

    m_readLabel->setMaskStatus(true);

    m_readLabel->setFixedSize(80,165);
    m_readLabel->move(800,25);
    Updater::getInstance()->addJumpLabel(m_readLabel);

    m_saveLabel->setPixmapPathGroup(saveNormal,savePress);
    m_saveLabel->setPixmapGroup(new QPixmap(saveNormal),new QPixmap(savePress));
    m_saveLabel->setMaskStatus(true);
    m_saveLabel->setFixedSize(80,165);
    m_saveLabel->move(20,25);
    Updater::getInstance()->addJumpLabel(m_saveLabel);

    //连接存档--clicked信号

}

void chievementWidget::intiMainLabel(QString cen,QString achInfo, QVector<QString> emblem, QString achID, QString stP, QString gL)
{
    m_centerLabel->setFixedSize(850,165);
    m_centerLabel->setScaledContents(true);
    m_centerLabel->setStyleSheet("border-image:url("+cen+");");
    m_centerLabel->move(25,25);

    m_achInfoLaebl->setFixedSize(300,60);
    m_achInfoLaebl->setText(achInfo);
    m_achInfoLaebl->move(100,30);

    m_achIDLabel->setText(QString("存档ID: ")+achID);
    m_storyProgressLabel->setText(QString("剧情进度: ")+stP);
    m_gameLevelLabel->setText(QString("存档难度: ")+gL);


    for(int i=0;i<3;i++)
    {
        m_emblems[i]->setFixedSize(60,60);
        m_emblems[i] ->setScaledContents(true);
        m_emblems[i]->setMask(QPixmap(emblem[i]).mask());
        m_emblems[i]->setPixmap(QPixmap(emblem[i]));
        m_emblems[i]->setPixmap(QPixmap(emblem[i]).scaled( m_emblems[i]->width(), m_emblems[i]->height()));
        m_emblems[i]->move(100+i*65,100);

        m_infoLabels[i]->setFixedSize(300,60);
        m_infoLabels[i]->move(500,30+i*65);
    }


}

void chievementWidget::initCenterLabel(QString cen)
{
    m_centerLabel->setFixedSize(850,165);
    m_centerLabel->setScaledContents(true);
    QPixmap *pix=new QPixmap(cen);
    qDebug()<<pix->isNull();
    m_centerLabel->setPixmap(QPixmap(cen).scaled(m_centerLabel->size()));

    //m_centerLabel->setStyleSheet("border-image:url("+cen+");");
    m_centerLabel->move(25,25);

}

void chievementWidget::initAchInfo(QString achInfo)
{
    m_achInfoLaebl->setFixedSize(300,60);
    m_achInfoLaebl->setText(achInfo);
    m_achInfoLaebl->move(100,30);
    Style::getInstance()->setLabelStyle(m_achInfoLaebl,2,2);
}

void chievementWidget::initEmblems(QVector<QString> emblem)
{
    for(int i=0;i<3;i++)
    {
        m_emblems[i]->setFixedSize(80,80);
        m_emblems[i] ->setScaledContents(true);
        //m_emblems[i]->setMask(QPixmap(emblem[i]).mask());
        //m_emblems[i]->setPixmap(QPixmap(emblem[i]));
        m_emblems[i]->setPixmap(QPixmap(emblem[i]).scaled( m_emblems[i]->width(), m_emblems[i]->height()));
        m_emblems[i]->move(100+i*105,100);
    }
}

void chievementWidget::initRecallInfo(QString achID, QString stP, QString gL)
{
    m_achIDLabel->setText(QString("存档ID: ")+achID);
    m_storyProgressLabel->setText(QString("剧情进度: ")+stP);
    m_gameLevelLabel->setText(QString("存档难度: ")+gL);

    for(int i=0;i<3;i++)
    {
        m_infoLabels[i]->setFixedSize(300,50);
        m_infoLabels[i]->move(500,32+i*50);
         Style::getInstance()->setLabelStyle(m_infoLabels[i],2,2);
    }
}


