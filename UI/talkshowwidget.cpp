#include "talkshowwidget.h"

TalkShowWidget::TalkShowWidget(QWidget *parent)
    : UIWidget{parent}
{
    resize(1600,300);
    m_headLabel=new QLabel(this);
    m_headLabel->setGeometry(25,25,250,250);

    m_storyShowLabel=new storyShowLabel(this);
    m_storyShowLabel->setGeometry(300,25,1000,250);
    m_storyShowLabel->setWordWrap(true);


    m_toolLabel=new QLabel (this);
    m_toolLabel->setGeometry(1325,25,250,250);

    Style::getInstance()->setLabelStyle(m_toolLabel,1,1);
    Style::getInstance()->setLabelStyleByPalete_25_white(m_storyShowLabel);
    Style::getInstance()->setWidgetBackground(this,3);


}

void TalkShowWidget::initToolLabelGroup(QVector<JumpLabel *> jpG)
{

}

void TalkShowWidget::setText(QString text)
{
    m_storyShowLabel->setText(text);
}

void TalkShowWidget::setHead(QPixmap headPix)
{
    m_headLabel->setPixmap(headPix.scaled(m_headLabel->size()));
}

void TalkShowWidget::setToolPix(QPixmap pix)
{
    m_toolLabel->setPixmap(pix.scaled(m_toolLabel->size()));
}

storyShowLabel *TalkShowWidget::getStoryShowLabel() const
{
return m_storyShowLabel;
}

