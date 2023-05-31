#include "choicewidget.h"

ChoiceWidget::ChoiceWidget(QWidget *parent)
    : QScrollArea{parent}
{

    // 实例化 QWidget
    m_mainWidget = new QWidget(this);

    // 实例化标题标签 titleLabel
    m_titleLabel = new QLabel(m_mainWidget);

    // 实例化分割标签 m_slipLabel
    m_slipLabel = new QLabel(m_mainWidget);

    // 实例化指示器标签 m_indicatorLabel
    m_indicatorLabel = new QLabel(m_mainWidget);
    m_indicatorLabel->setVisible(false);
    m_indicatorAvailable=false;



    m_indicatorLocationRight=false;
    m_currentLabel=nullptr;
}

QWidget *ChoiceWidget::getWidget()
{
    return m_mainWidget;
}

void ChoiceWidget::initTitleLabel(QLabel *titleLabel, QRect rect)
{
    delete m_titleLabel;
    m_titleLabel=titleLabel;
    m_titleLabel->setParent(m_mainWidget);
    m_titleLabel->setGeometry(rect);

}

void ChoiceWidget::initSlipLabel(QLabel *slipLabel, QRect rect)
{
    delete m_slipLabel;
    m_slipLabel=slipLabel;
    m_slipLabel->setParent(m_mainWidget);
    m_slipLabel->setGeometry(rect);
}

void ChoiceWidget::initChoiceLabel(QVector<JumpLabel *> jumpGroup, QVector<QRect> rectGroup)
{
    for(auto it:m_jumpLabelGroup )
    {
        delete it;
    }
    m_jumpLabelGroup.clear();

    m_jumpLabelGroup=jumpGroup;
    int i=0;
    for(auto it:m_jumpLabelGroup)
    {

        it->setGeometry(rectGroup[i]);
        ++i;
    }

    setCurrentLabel(m_jumpLabelGroup[0]);

}

void ChoiceWidget::setIndicatorAvailable(bool flag)
{
    m_indicatorAvailable=flag;
}

void ChoiceWidget::setCurrentLabel(JumpLabel *curLabel)
{

    if(m_currentLabel!=nullptr)
    {
        m_currentLabel->updatePix();
        m_currentLabel=curLabel;
        m_currentLabel->setStyleSheet("border-image:url("+m_currentLabelPixPath+")");

    }
    else
    {
        m_currentLabel=curLabel;
        m_currentLabel->setStyleSheet("border-image:url("+m_currentLabelPixPath+")");
    }

}

void ChoiceWidget::initIndicator(QLabel *indicatorLabel, bool right)
{
    m_indicatorLabel=indicatorLabel;
    m_indicatorLocationRight=right;
}

void ChoiceWidget::setCurrentLabelPixPath(const QString &newCurrentLabelPixPath)
{
    m_currentLabelPixPath = newCurrentLabelPixPath;
}

void ChoiceWidget::paintEvent(QPaintEvent *e)
{

}

int ChoiceWidget::getCurrentCharacter()
{
    return m_currentLabel->getCardID();
}
