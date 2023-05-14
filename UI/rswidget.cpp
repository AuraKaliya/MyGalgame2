#include "rswidget.h"

RSWidget* RSWidget::instance = nullptr;

RSWidget::RSWidget(QWidget *parent) : QWidget(parent)
{

    // constructor implementation
    m_count =0;
    m_showArea=new QScrollArea(this);
    m_showArea->setFixedSize(1000,660);
    m_showArea->move(300,240);

    m_showWidget= new QWidget(m_showArea);
    m_showWidget->setWindowFlags(Qt::FramelessWindowHint);
    m_showArea->setWidget(m_showWidget);

    addLabel=new JumpLabel(m_showWidget);
    addLabel->setFixedSize(850,150);
    addLabel->move(0,10+m_count*220);

}

RSWidget::~RSWidget()
{
    // destructor implementation

}

RSWidget* RSWidget::getInstance(QWidget* parent)
{
    if (instance == nullptr)
    {
        instance = new RSWidget(parent);
    }
    return instance;
}

void RSWidget::addAchWidget(chievementWidget *achWidget)
{
    achWidget->setParent(m_showWidget);
    achWidget->move(0,10+m_count*220);
    ++m_count;

    m_showWidget->resize(m_showArea->width(),20+(m_count+1)*220);
    addLabel->move(0,10+m_count*220);

}

void RSWidget::initAddLabel(QString normalUrl, QString PressUrl)
{
    addLabel->setPixmapPathGroup(normalUrl,PressUrl);
    Updater::getInstance()->addJumpLabel(addLabel);
    connect(addLabel,&JumpLabel::clicked,this,&RSWidget::showNewAchWidget);

}

void RSWidget::showNewAchWidget()
{
    qDebug()<<"RSWidget::showNewAchWidget";
}
