#include "characterstoryshowwidget.h"

CharacterStoryShowWidget* CharacterStoryShowWidget::instance = nullptr;

CharacterStoryShowWidget* CharacterStoryShowWidget::getInstance(QWidget *parent)
{
    if(instance == nullptr)
    {
        instance = new CharacterStoryShowWidget(parent);
    }
    return instance;
}

void CharacterStoryShowWidget::initCharacterStory(QString tiltle, QString story)
{
    m_storyLabel->setText(story);
    m_titleLabel->setText(tiltle);
    m_storyLabel->adjustSize();
    adjustSize();

}


CharacterStoryShowWidget::CharacterStoryShowWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("border-image:url(:/UI/RESOURCE/test_transparency3.png);");
    resize(400,900);
    setWindowFlags(Qt::FramelessWindowHint);




    m_titleLabel=new QLabel(this);
    m_storyLabel=new QLabel(this);

    m_titleLabel->setFixedSize(400,100);
    m_titleLabel->move(0,0);
    m_titleLabel->setFont(QFont("楷体",45,QFont::Bold,Qt::black));
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setWordWrap(true);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    m_titleLabel->setPalette(pa);
     Style::getInstance()->setLabelStyle(m_titleLabel,2,7);


    m_storyLabel->setGeometry(0,120,400,50);
    m_storyLabel->setMinimumWidth(400);
    m_storyLabel->setFixedWidth(400);
    m_storyLabel->setWordWrap(true);
    m_storyLabel->setFont(QFont("楷体",15,QFont::Bold,Qt::black));
    m_storyLabel->setAlignment(Qt::AlignLeft);
    Style::getInstance()->setLabelStyle(m_storyLabel,2,6);
//    QPalette pa2;
//    pa2.setColor(QPalette::WindowText,Qt::black);
//    m_storyLabel->setPalette(pa2);







}

CharacterStoryShowWidget::~CharacterStoryShowWidget()
{
    delete instance;
    instance = nullptr;
}
