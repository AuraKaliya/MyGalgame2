#include "carouselwidget.h"

CarouselWidget* CarouselWidget::instance = nullptr;

CarouselWidget::CarouselWidget(QWidget *parent) : QWidget(parent)
{
    m_mapWidget=new CarouselMapWidget(this);
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
}

void CarouselWidget::initStoryInfoWidget(StoryInfoWidget *stIW, QRect rect)
{
    m_storyInfoWidget=stIW;
    m_storyInfoWidget->setParent(this);
    m_storyInfoWidget->setGeometry(rect);


}

void CarouselWidget::initChoiceWidget(ChoiceWidget *cw, QRect rect)
{
    m_choiceWidget=cw;
    m_choiceWidget->setParent(this);
    m_choiceWidget->setGeometry(rect);
}
