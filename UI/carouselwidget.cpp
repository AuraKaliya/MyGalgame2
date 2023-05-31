#include "carouselwidget.h"

CarouselWidget* CarouselWidget::instance = nullptr;

CarouselWidget::CarouselWidget(QWidget *parent) : QWidget(parent)
{
   // m_mapWidget=new CarouselMapWidget(this);
    nowStoryIdx=0;
}

int CarouselWidget::getNowStoryIdx() const
{
    return nowStoryIdx;
}

CarouselWidget* CarouselWidget::getInstance(QWidget *parent)
{
    if (instance == nullptr) {
        instance = new CarouselWidget(parent);
    }
    return instance;
}

CarouselMapWidget* CarouselWidget::mapWidget()
{
    return m_mapWidget;
}

void CarouselWidget::initCaroselMapWidget(CarouselMapWidget *mapWidget,QRect rect)
{
    m_mapWidget=mapWidget;
    m_mapWidget->setParent(this);
    m_mapWidget->setGeometry(rect);
   // m_mapWidget->setVisible(false);
    //
}

void CarouselWidget::initStoryInfoWidget(StoryInfoWidget *stIW, QRect rect)
{
    m_storyInfoWidget=stIW;
    m_storyInfoWidget->setParent(this);
    m_storyInfoWidget->setGeometry(rect);

    //m_storyInfoWidget->setVisible( false);   排查异常按钮
   //
}

void CarouselWidget::initChoiceWidget(ChoiceWidget *cw, QRect rect)
{
    m_choiceWidget=cw;
    m_choiceWidget->setParent(this);
    m_choiceWidget->setGeometry(rect);
    // m_choiceWidget->setVisible(false);
}

void CarouselWidget::initBackgroundPix(QString bkUrl)
{
    m_backgroundPix=new QPixmap(bkUrl);
}

void CarouselWidget::initChoiced()
{
    qDebug()<<"谢谢谢谢谢谢3"<<Qt::endl;
    characterChoiced(m_choiceWidget->getCurrentCharacter());
    storyChoiced(m_mapWidget->getCurrentStoryID());
    connect(m_mapWidget,&CarouselMapWidget::nowStory,this,&CarouselWidget::storyChoiced);
    qDebug()<<"谢谢谢谢谢谢4"<<Qt::endl;
}

void CarouselWidget::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,this->width(),this->height()),*m_backgroundPix);

   // qDebug()<<this->children();
}


void CarouselWidget::characterChoiced(int i)
{
    QVector<JumpLabel*> tmpJumpGroup;
    QVector <Story*> tmpStory=CharacterHub::getInstance()->findCharatcersStory(i);

    for(auto it :tmpStory)
    {
        JumpLabel* tmpL=new JumpLabel(m_mapWidget);
        tmpL->setVisible(true);
        tmpL->setCardID(it->getID());
        tmpL->setPixmapPathGroup(it->getCoverPixUrl(),it->getCoverPixUrl());
        qDebug()<<it->getCoverPixUrl();
        //tmpL->setStyleSheet("border-image:url("+it->getCoverPixUrl()+")");
        tmpL->setStyleSheet("background:rgb(200,200,200);");
        tmpL->updatePix();
        //tmpL->show();
        tmpJumpGroup<<tmpL;
        connect(tmpL,&JumpLabel::choiceCard,this,&CarouselWidget::storyChoiced);
        connect(tmpL,&JumpLabel::me,m_mapWidget,&CarouselMapWidget::setCurrentStoryByLabel);
    }

    m_mapWidget->initCarousel(tmpJumpGroup);
    m_storyInfoWidget->initTachie(CharacterHub::getInstance()->findCharacter(i));
    storyChoiced(tmpStory[0]->getID());
}


void CarouselWidget::storyChoiced(int i)
{

    if(nowStoryIdx==i)
    {
        //qDebug()<<"sssss31231231";
        emit joinStory(i);
    }

    m_storyInfoWidget->initStory(CharacterHub::getInstance()->findStory(i)->title(),CharacterHub::getInstance()->findStory(i)->Introduction());
    nowStoryIdx=i;
}
