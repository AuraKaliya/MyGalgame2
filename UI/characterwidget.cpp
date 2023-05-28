#include "characterwidget.h"

CharacterWidget* CharacterWidget::instance = nullptr;


CharacterWidget *CharacterWidget::getInstance(QWidget *parent)
{
    if(instance == nullptr)
    {
        instance = new CharacterWidget(parent);
    }
    return instance;
}

CharacterWidget::CharacterWidget(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(1600,900);
    m_characterDetailShowWidget=new QStackedWidget(this);
    m_characterRect=QRect(475,-75,625,(int)((16.0/9.0)*625));

    m_characterHeadRect= new QRect(475,0,625,200);
    m_characterBraRect=new QRect(475,200,625,200);
    m_characterLegRect=new QRect(475,400,625,200);
    m_characterFootRect=new QRect(475,600,625,200);
    characterBodyRect<<m_characterHeadRect<<m_characterBraRect<<m_characterLegRect<<m_characterFootRect;

    characterBodyReflect.insert(m_characterHeadRect,"开心");
    characterBodyReflect.insert(m_characterBraRect,"害羞");
    characterBodyReflect.insert(m_characterLegRect,"生气");
    characterBodyReflect.insert(m_characterFootRect,"沮丧");





}

void CharacterWidget::initCharacterHubWidget(CharacterHubWidget *charaHubWidget, QRect rect)
{
    m_charaHubWidget=charaHubWidget;
    m_charaHubWidget->setParent(this);
    m_charaHubWidget->setGeometry(rect);

}

void CharacterWidget::initCharacterInfoGroup(QVector<JumpLabel *> characterInfoGroup, QRect InfoRect, int space)
{
    //InfoRect 用于规定起始x、y和每个框的w、h；

    int i=0;
    for(auto it:characterInfoGroup)
    {
        it->setParent(this);
        it->setGeometry(InfoRect.x(),InfoRect.y()+((space+InfoRect.height())*i),InfoRect.width(),InfoRect.height());
        ++i;
        m_characterInfoGroup.append(it);

        it->setVisible(false);
    }

}





void CharacterWidget::initCharacterInfoShowWidget(CharacterInfoShowWidget *InfoShowWidget, QRect InfoShowRect)
{
    m_infoShowWidget=InfoShowWidget;
    m_infoShowWidget->setParent(this);
    m_characterDetailShowWidget->addWidget(m_infoShowWidget);
    m_characterDetailShowWidget->setGeometry(InfoShowRect);



    m_infoShowWidgetGroup<<m_infoShowWidget;



}

void CharacterWidget::initCharacterStoryWidget(CharacterStoryShowWidget *storyShowWidget, QRect InfoShowRect)
{
    m_storyShowWidget=storyShowWidget;
    m_storyArea=new QScrollArea(this);
    m_characterDetailShowWidget->addWidget(m_storyArea);
    m_characterDetailShowWidget->setGeometry(InfoShowRect);
    m_storyShowWidget->setParent(m_storyArea);
    m_storyArea->setWidget(m_storyShowWidget);
    m_storyArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_storyArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_storyArea->setGeometry(0,0,InfoShowRect.width(),InfoShowRect.height());
    m_storyShowWidget->move(0,0);
    m_infoShowWidgetGroup<<m_storyArea;
}



void CharacterWidget::initLink()
{
    for(int i=0;i<m_infoShowWidgetGroup.size();i++)
    {
        m_characterInfoGroup[i]->setDestination(m_infoShowWidgetGroup[i]);
        connect(m_characterInfoGroup[i],SIGNAL(jump(QWidget*)),m_characterDetailShowWidget,SLOT(setCurrentWidget(QWidget*)));
        connect(m_characterInfoGroup[i],&JumpLabel::clicked,this,[=](){
            OptionChanged(m_characterInfoGroup[i]);
        });

    }
    NowOptionLabel=m_characterInfoGroup[0];
    OptionChanged(NowOptionLabel);
}

void CharacterWidget::setBackground(QString bkgPath)
{
    m_backgroundPix=new QPixmap();
    m_backgroundPix->load(bkgPath);
}

void CharacterWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,width(),height()),*m_backgroundPix);
    //painter.set
    QPainter painter2(this);

    if(!m_characterTachie->isNull()&&!m_characterRect.isNull())
    {
        painter2.drawPixmap(m_characterRect,*m_characterTachie);
    }

}

void CharacterWidget::setNowCharacterGes(QString gestPath)
{
    m_characterTachie=new QPixmap(gestPath);
     qDebug()<<m_characterTachie->isNull()<<"helllllll2";

}

void CharacterWidget::mousePressEvent(QMouseEvent *e)
{
     QPoint point = e->pos();
     if(e->button()==Qt::LeftButton)
     {
        for(int i=0;i<characterBodyRect.size();++i)
        {
            if(characterBodyRect[i]->contains(point))
            {
                setNowCharacterGes(m_nowCharacter->getGesture(characterBodyReflect.value(characterBodyRect[i])));
                CharacterInfoShowWidget::getInstance()->showLoveLines(m_nowCharacter->getLines(linesKey[QRandomGenerator::global()->bounded(0,5)]));
                update();
                break;
            }
        }
     }


}

void CharacterWidget::hubShow()
{
    for(auto it:m_characterInfoGroup)
    {
        it->setVisible(false);
    }
}

void CharacterWidget::hubHide()
{
    for(auto it:m_characterInfoGroup)
    {
        it->setVisible(true);
    }
}

void CharacterWidget::setNowCharacter(Character *ch)
{
    m_nowCharacter=ch;
    QString gesPath=ch->getGesture("正常");
    setNowCharacterGes(gesPath);
    CharacterStoryShowWidget::getInstance()->initCharacterStory(m_nowCharacter->storyTitle(),m_nowCharacter->story());
    update();
}

void CharacterWidget::OptionChanged(JumpLabel *jL)
{

    NowOptionLabel->updatePix();
    jL->setStyleSheet("border-image:url(:/UI/RESOURCE/test_choiceLabel2.png);");
    NowOptionLabel=jL;
}

