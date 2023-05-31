#include "storyinfowidget.h"

StoryInfoWidget::StoryInfoWidget(QWidget *parent)
    : QWidget{parent}
{
    m_tachieLabel = new TachieLabel(this);
    m_storyIntroArea = new QScrollArea(this);
    m_storyIntroWidget = new QWidget(this);
    m_storyHeadLabel = new QLabel(m_storyIntroWidget);
    m_slipLabel = new QLabel(m_storyIntroWidget);
    m_storyIntroLabel = new QLabel(m_storyIntroWidget);
    resize(1200,640);
}

void StoryInfoWidget::initTachie(Character *character, QRect rect)
{
    m_tachieLabel->setGeometry(rect);
    m_character=character;

    m_tachieLabel->initCharacter(m_character,rect);

}

void StoryInfoWidget::initStory(QString storyTitle, QString storyIntroduction)
{
    m_storyTitle=storyTitle;
    m_storyIntroduction=storyIntroduction;

    m_storyHeadLabel->setText(m_storyTitle);
    m_storyHeadLabel->setGeometry(10,0,760,100);
    m_storyHeadLabel->setVisible(true);

    m_slipLabel->setGeometry(0,110,780,30);
    m_slipLabel->setStyleSheet("border-image:url(:/UI/RESOURCE/test_splite2.png)");
    m_slipLabel->setVisible(true);

    m_storyIntroLabel->setText(m_storyIntroduction);
    m_storyIntroLabel->setWordWrap(true);
    m_storyIntroLabel->adjustSize();
    m_storyIntroLabel->move(10,150);
    m_storyIntroLabel->setVisible(true);

    m_storyIntroArea->setGeometry(370,0,780,640);
    m_storyIntroArea->setWidget(m_storyIntroWidget);
    m_storyIntroWidget->adjustSize();
    m_storyIntroWidget->move(0,0);

    m_storyIntroArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_storyIntroArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


   // m_characterStoryWidget=CharacterStoryShowWidget::getInstance();
    //m_characterStoryWidget->initCharacterStory(storyTitle,storyIntroduction);

    Style::getInstance()->setLabelStyleByPalete_45_white(m_storyHeadLabel);
    Style::getInstance()->setLabelStyleByPalete_25_white(m_storyIntroLabel);

}

void StoryInfoWidget::initStory()
{

}

void StoryInfoWidget::setNowStory(int)
{

}

