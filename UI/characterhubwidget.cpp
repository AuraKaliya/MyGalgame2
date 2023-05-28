 #include "characterhubwidget.h"


CharacterHubWidget::CharacterHubWidget(QWidget *parent)
    : QWidget{parent}
{
    resize(450,900);
   setWindowFlags(Qt::FramelessWindowHint);
   //setAttribute(Qt::WA_TranslucentBackground,true);

    m_searchBlock=new Searchblok();
    m_searchBlock->setParent(this);
    m_searchBlock->setGeometry(25,50,400,30);

    m_characterShowArea=new QScrollArea(this);
    m_characterShowWidget=new QWidget(m_characterShowArea);

    m_characterShowArea->setGeometry(25,100,400,600);

    m_characterShowArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_characterShowArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_characterShowWidget->setWindowFlags(Qt::FramelessWindowHint);
    m_characterShowArea->setWidget(m_characterShowWidget);
    m_showAreaRect=m_characterShowArea->geometry();
    m_characterShowWidget->setGeometry(m_showAreaRect);


   // m_stackedLayout=new QStackedLayout();
    m_showLayout=new QGridLayout();






   // m_stackedLayout->
//    for(int i=1;i<5;i++)
//    {
//        JumpLabel * tmpJ=new JumpLabel(m_characterShowWidget);
//        m_characterLabelGroup<<tmpJ;
//        tmpJ->setPixmapPathGroup(":/UI/RESOURCE/test_CharacterCardPix"+QString::number(i)+".png",":/UI/RESOURCE/test_CharacterCardSmallPix"+QString::number(i)+".png");
//        tmpJ->setFixedSize(90,120);
//        m_showLayout->addWidget(tmpJ,(i-1)/3,(i-1)%3,Qt::AlignCenter);
//        m_characterShowWidget->resize(m_characterShowWidget->width(),((i-1)/3+1)*150);
//    }

   // m_characterShowWidget->setLayout(m_showLayout);

    m_showLayout->setSpacing(10);
    m_showLayout->setContentsMargins(0,5,0,5);


    m_showWidgetRect=m_characterShowWidget->geometry();

    //m_hideAreaRect=QRect(25,100,85,600);
    //m_hideWidgetRect=QRect(0,0,85,m_characterLabelGroup.size()*70);








    m_slideBlock=new SlideBlock();
    m_slideBlock->setParent(this);
    m_slideBlock->setRect(QRect(25,775,400,85));
    m_slideBlock->setGeometry(340,775,85,85);
    m_slideBlock->setFixPos(m_slideBlock->pos());


    connect(m_slideBlock,&SlideBlock::valueMax,this,&CharacterHubWidget::hideWidget);
    connect(m_slideBlock,&SlideBlock::reset,this,&CharacterHubWidget::showWidget);


    setStyleSheet("border-image:url(:/UI/RESOURCE/test_transparency3.png);");
    //hideWidget();

}

void CharacterHubWidget::initCharacterHub()
{
    int i=0;
    for(auto it:CharacterHub::getInstance()->getCharaList())
    {
        JumpLabel * tmpJ=new JumpLabel(m_characterShowWidget);
        m_characterLabelGroup<<tmpJ;
        tmpJ->setCardID(it->getID());
       //tmpJ->setPixmapPathGroup(":/UI/RESOURCE/test_CharacterCardPix"+QString::number(i)+".png",":/UI/RESOURCE/test_CharacterCardSmallPix"+QString::number(i)+".png");
        tmpJ->setPixmapPathGroup(it->cardPixPath(),it->cardSmallPixPath());
        tmpJ->setFixedSize(m_cardSize);
//        tmpJ->setFixedSize(m_cardSize);
//        m_showLayout->addWidget(tmpJ,(i)/3,(i)%3,Qt::AlignCenter);
        m_characterShowWidget->resize(m_characterShowWidget->width(),((i-1)/3+1)*150);
        m_showLayout->addWidget(tmpJ,(i)/3,(i)%3,Qt::AlignCenter);
        m_characterShowWidget->setLayout(m_showLayout);
        connect(tmpJ,&JumpLabel::choiceCard,this,&CharacterHubWidget::characterChoiced);

        ++i;
    }

     m_hideWidgetRect=QRect(0,0,85,m_characterLabelGroup.size()*70);
    CharacterInfoShowWidget::getInstance()->initCharacterInfomation(CharacterHub::getInstance()->findCharacter(m_characterLabelGroup[0]->getCardID()));
     emit characterClicked(CharacterHub::getInstance()->findCharacter(m_characterLabelGroup[0]->getCardID()));
}

void CharacterHubWidget::initRect(QRect showRect, QRect hideRect)
{
    m_showRect=showRect;
    m_hideRect=hideRect;
}

void CharacterHubWidget::initCardSize(QSize cardSize, QSize cardSmallSize)
{
    m_cardSize=cardSize;
    m_cardSmallSize=cardSmallSize;
}

void CharacterHubWidget::initAreaRect(QRect showRect, QRect hideRect)
{
    m_showAreaRect=showRect;
    m_hideAreaRect=hideRect;
}

void CharacterHubWidget::setSpace(int sp)
{
    m_space=sp;
}



void CharacterHubWidget::hideWidget()
{
    delete m_showLayout;
    m_showLayout=new QGridLayout();
    int i=0;
    for (auto it:m_characterLabelGroup)
    {
        it->changePix();
        //it->setFixedSize(65,65);
        it->setFixedSize(m_cardSmallSize);
        m_showLayout->addWidget(it,i++,0,Qt::AlignCenter);
    }

    //m_characterShowArea->setGeometry(25,100,85,600);
    m_characterShowArea->setGeometry(m_hideAreaRect);
    m_characterShowWidget->setGeometry(0,0,m_hideAreaRect.width(),m_characterLabelGroup.size()*70);

    m_characterShowWidget->setLayout(m_showLayout);
    m_searchBlock->setVisible(false);
    resize(m_hideRect.size());

    emit widgetHide();

}

void CharacterHubWidget::showWidget()
{

    delete m_showLayout;
    m_showLayout=new QGridLayout();
    int i=0;
    for (auto it:m_characterLabelGroup)
    {
        it->changePix();
        //it->setFixedSize(90,120);
        it->setFixedSize(m_cardSize);
        m_showLayout->addWidget(it,i/3,i%3,Qt::AlignCenter);
        ++i;
    }

    m_characterShowArea->setGeometry(m_showAreaRect);
    m_characterShowWidget->setGeometry(0,0,m_characterShowArea->width(),((i-1)/3+1)*150);
    m_characterShowWidget->setLayout(m_showLayout);

    m_searchBlock->setVisible(true);
    resize(m_showRect.size());

    emit widgetShow();
}

void CharacterHubWidget::characterChoiced(int id)
{
    Character* tmp=CharacterHub::getInstance()->findCharacter(id);
    CharacterInfoShowWidget::getInstance()->initCharacterInfomation(tmp);
    emit characterClicked(tmp); //  不行 需要新建一个用于paint立绘的类
}
