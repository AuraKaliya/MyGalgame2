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
     //addLabel->setText("addLabel");

    m_choiceLabelLeft=new QLabel(this);
    m_choiceLabelLeft->setFixedSize(80,200);
    m_choiceLabelLeft->move(200,240);
    m_choiceLabelRight=new QLabel(this);
    m_choiceLabelRight->setFixedSize(80,200);
    m_choiceLabelRight->move(1320,240);


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
    //achWidget->setFixedSize(m_showWidget->width()-50,achWidget->height());
    achWidget->move(50,10+m_count*220);
    ++m_count;

    m_showWidget->resize(m_showArea->width()-20,20+(m_count+1)*220);

    addLabel->move(75,10+m_count*220);

}

void RSWidget::initAddLabel(QString normalUrl, QString PressUrl)
{
    addLabel->setPixmapPathGroup(normalUrl,PressUrl);
    addLabel->setPixmapGroup(new QPixmap(normalUrl),new QPixmap(PressUrl));
    addLabel->setMaskStatus(true);
    //Style::getInstance()->setLabelStyle(addLabel,)
    Updater::getInstance()->addJumpLabel(addLabel);
    connect(addLabel,&JumpLabel::clicked,this,&RSWidget::showNewAchWidget);

}

void RSWidget::initChoiceLabels(QImage imgLeft, QImage imgRight)
{
    m_choiceLabelLeft->setPixmap(QPixmap::fromImage(imgLeft).scaled(m_choiceLabelLeft->size()));
    m_choiceLabelRight->setPixmap(QPixmap::fromImage(imgRight).scaled(m_choiceLabelLeft->size()));

}

void RSWidget::initBackground(QString path)
{
    m_backgroundImage=new QPixmap(path);
    Style::getInstance()->setWidgetBackground(m_showArea,3);
    Style::getInstance()->setWidgetBackground(m_showWidget,1);
    //Style::getInstance()->setWidgetBackground(this,2);
}

void RSWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,width(),height()),*m_backgroundImage);
}

void RSWidget::showNewAchWidget()
{
    qDebug()<<"RSWidget::showNewAchWidget";
}
