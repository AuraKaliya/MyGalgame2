#include "mainwidget.h"

MainWidget* MainWidget::m_instance = nullptr;

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    // constructor
    buttonStautes=false;
}

MainWidget* MainWidget::getInstance(QWidget *parent)
{
    if(m_instance == nullptr)
    {
        m_instance = new MainWidget(parent);
    }
    return m_instance;
}

void MainWidget::initMainShowLabel(QVector<JumpLabel *> label, QVector<QRect> rect)
{
    m_mainShowLabelGroup=label;
    for(int i=0;i<label.size();++i)
    {
        m_mainShowLabelGroup[i]->setParent(this);
        m_mainShowLabelGroup[i]->setGeometry(rect[i]);
    }
}

void MainWidget::initToolShowLabel(QVector<JumpLabel *> label, QVector<QRect> rect)
{
    m_toolShowLabelGroup=label;
    for(int i=0;i<label.size();++i)
    {
        m_toolShowLabelGroup[i]->setParent(this);
        m_toolShowLabelGroup[i]->setGeometry(rect[i]);
        m_toolShowLabelGroup[i]->setVisible(false);
    }
}

void MainWidget::initToolButton(QPixmap pix,QString pixPath)
{
    m_toolShowButton=new QPushButton(this);
    m_toolShowButton->setGeometry(1460,760,130,130);
    m_toolShowButton->setMask(pix.mask());
    m_toolShowButton->setStyleSheet("border-image:url("+pixPath+");");

}

void MainWidget::initToolButton(QPixmap maskPix, QString pixPathHide, QString pixPathShow)
{
    m_toolShowButton=new QPushButton(this);
    m_toolShowButton->setGeometry(1460,760,130,130);
    m_toolShowButton->setMask(maskPix.mask());
    m_toolShowButton->setStyleSheet("border-image:url("+pixPathHide+");");
    buttonStautes=false;
    hidePixPath=pixPathHide;
    showPixPath=pixPathShow;
    QObject::connect(m_toolShowButton,&QPushButton::clicked,[this](){
        if(buttonStautes){
            hideToolList();
        }
        else{
            showToolList();
        }
    });
}

void MainWidget::initTachieLabel(TachieLabel *tachieLabel, QRect rect)
{
    m_tachieLabel=tachieLabel;
    m_tachieLabel->setVisible(true);
    m_tachieLabel->setParent(this);
    m_tachieLabel->setGeometry(rect);
   // m_tachieLabel->setText("hhhhhh");
   // m_tachieLabel->setStyleSheet("background-color:rgb(200,101,102);");
    //qDebug()<<"233399999";
   // qDebug()<<m_tachieLabel->geometry();
}

void MainWidget::setHeadWidget(HeadWidget *head, QRect rect)
{
    m_head=head;
    m_head->setParent(this);
    m_head->setGeometry(rect);

}

void MainWidget::setBackground(QString bkgPath)
{

    m_backgroundImage=new QPixmap(bkgPath);


}

void MainWidget::paintEvent(QPaintEvent *e)
{
   QPainter painter(this);
   painter.drawPixmap(QRect(0,0,width(),height()),*m_backgroundImage);
   qDebug()<<m_tachieLabel->isVisible();

}

void MainWidget::showToolList()
{
    //m_toolShowButton
    QPropertyAnimation *animation = new QPropertyAnimation(m_toolShowButton,"pos");
    animation->setDuration(1000);

    QObject::connect(animation,&QPropertyAnimation::finished,[this](){
       m_toolShowButton->setStyleSheet("border-image:url("+showPixPath+");");
        buttonStautes=true;
       for(auto it:m_toolShowLabelGroup)
        {
            it->setVisible(true);
           qDebug()<<it->geometry()<<" "<<it->isVisible();
        }
       //qDebug()<<m_toolShowLabelGroup;
    });

    QPoint targetPos=QPoint(900,760);
    animation->setEndValue(targetPos);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWidget::hideToolList()
{
    //m_toolShowButton
    for(auto it:m_toolShowLabelGroup)
    {
        it->setVisible(false);
    }
    QPropertyAnimation *animation = new QPropertyAnimation(m_toolShowButton,"pos");
    animation->setDuration(1000);

    QObject::connect(animation,&QPropertyAnimation::finished,[this](){
        m_toolShowButton->setStyleSheet("border-image:url("+hidePixPath+");");
        buttonStautes=false;
    });

    QPoint targetPos=QPoint(1460,760);
    animation->setEndValue(targetPos);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
