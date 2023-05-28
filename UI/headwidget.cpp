#include "headwidget.h"

HeadWidget::HeadWidget(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(550,250);
    setWindowFlags(Qt::FramelessWindowHint);
    m_infoLabel =new QLabel(this);
    m_SRIDLabel=new QLabel(this);
    m_StoryProgressLabel=new QLabel(this);
    m_headLabel=new JumpLabel(this);
    m_frameLabel=new QLabel(this);


    m_infoLabel->setGeometry(95,10,450,220);
    m_SRIDLabel->setGeometry(105,20,430,80);
    m_StoryProgressLabel->setGeometry(105,120,430,80);


    m_headLabel->setGeometry(25,20,200,200);

    // setStyleSheet("border-image:url(:/UI/RESOURCE/test_transparency.png);");

}

void HeadWidget::initPix(QPixmap *head, QPixmap *infoLabel)
{
    m_infoLabel->setMask(infoLabel->mask());
    m_infoLabel->setPixmap(infoLabel->scaled(m_infoLabel->size()));


    m_headLabel->setPixmapGroup(head,head);
    //m_headLabel->setMask(head->mask());
    m_headLabel->setPixmap(head->scaled(m_headLabel->size()));
    m_headLabel->setVisible(true);

}

void HeadWidget::setFrame(QPixmap *framePix)
{

}

void HeadWidget::initInfoText(QString RSID, QString StoryProgress)
{
    m_SRIDLabel->setText(QString("存档ID："+RSID));
    m_StoryProgressLabel->setText(QString("剧情进度："+StoryProgress));
}

QLabel *HeadWidget::SRIDLabel() const
{
    return m_SRIDLabel;
}

QLabel *HeadWidget::StoryProgressLabel() const
{
    return m_StoryProgressLabel;
}
