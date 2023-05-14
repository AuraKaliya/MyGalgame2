#include "settingwidget.h"

SettingWidget* SettingWidget::m_instance=nullptr;

SettingWidget* SettingWidget::getInstance(QWidget *parent)
{
    if(m_instance==nullptr)
    {
        m_instance=new SettingWidget(parent);
    }
    return m_instance;
}

SettingWidget::SettingWidget(QWidget *parent)
    : QWidget{parent}
{
    L2WTabel.clear();
    m_choiceWidget=new QWidget(this);
    m_choiceWidget->setWindowFlags(Qt::FramelessWindowHint);

    m_settingShowWidget =new QStackedWidget(this);
    m_settingShowWidget->setWindowFlags(Qt::FramelessWindowHint);
    m_settingShowWidget->setAttribute(Qt::WA_TranslucentBackground,true);
    m_settingShowWidget->setFixedSize(1200,650);
    m_settingShowWidget->move(400,250);

    //设置整个m_settingShowWidget的背景

    //设置整个m_settingShowWidget的背景

    m_hideStatueTimer=new QTimer(this);
    m_showStatueTimer=new QTimer(this);
    connect(m_hideStatueTimer,&QTimer::timeout,this,[=](){
        if(checkedShow())
        {
            showWidgetAnimated();
        }
    });
    connect(m_showStatueTimer,&QTimer::timeout,this,[=](){
        if(checkedHide())
        {
            hideWidgetAnimated();
        }
    });
    m_hideStatueTimer->start(100);
    this->installEventFilter(this);






}

bool SettingWidget::checkedShow()
{
    QPoint cursorPos=mapFromGlobal(QCursor::pos());
    return ((cursorPos.x()<(this->width()/10))&&(!m_choiceWidget->isVisible())&&(cursorPos.x()>0));
}

bool SettingWidget::checkedHide()
{
    QPoint widgetPos=mapFromGlobal(QCursor::pos());
    return (m_choiceWidget->isVisible()&&!m_choiceWidget->rect().contains(widgetPos));
}


void SettingWidget::initChoiceWidget(QString title, QVector<JumpLabel *> labelGroup, QString choicePix)
{
    m_choiceWidget->setFixedSize(400,height());

    m_choiceWidget->setStyleSheet("border-image:url(:/UI/RESOURCE/test_transparency3.png);");
    m_titleLabel2=new QLabel(m_choiceWidget);
    m_titleLabel2->setFont(QFont("楷体",30,QFont::Bold,Qt::white));
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    m_titleLabel2->setPalette(pa);
    m_titleLabel2->setScaledContents(true);
    m_titleLabel2->setStyleSheet("border-image:url(:/UI/RESOURCE/test_transparency2.png);");
    m_titleLabel2->setAlignment(Qt::AlignCenter);
    m_titleLabel2->setText(title);
    m_titleLabel2->setFixedSize(400,200);
    m_titleLabel2->move(0,0);

    m_choiceIconLabel =new QLabel(m_choiceWidget);
    m_choiceIconLabel->setStyleSheet("");
    QPixmap pix(choicePix);
    m_choiceIconLabel->setScaledContents(true);
    m_choiceIconLabel->setMask(pix.mask());
    m_choiceIconLabel->setFixedSize(80,80);

    m_choiceIconLabel->setPixmap(pix);

    // m_choiceIconLabel->move(310,);
    int i=0;
    for(auto it :labelGroup)
    {
        it->setParent(m_choiceWidget);
        it->move(30,250+i*100);
        it->setDestination(W2ATabel.value(L2WTabel.value(it->text())));
        QObject::connect(it,SIGNAL(jump(QWidget*)),m_settingShowWidget,SLOT(setCurrentWidget(QWidget*)));
        QObject::connect(it,&JumpLabel::clicked,this,[=](){
            m_choiceIconLabel->setVisible(true);
            m_nowLabel->updatePix();
            m_nowLabel=it;
            m_nowLabel->setStyleSheet("border-image:url("+m_nowLabelPix+");");
            m_choiceIconLabel->move(310,(it->y()+0.5*(it->height()-m_choiceIconLabel->height())));

        });
        ++i;
    }
    m_nowLabel=labelGroup[0];
    m_nowLabel->setStyleSheet("border-image:url("+m_nowLabelPix+");");
    m_choiceIconLabel->setVisible(true);
    m_choiceIconLabel->move(310,(labelGroup[0]->y()+0.5*(labelGroup[0]->height()-m_choiceIconLabel->height())));
    m_choiceWidget->move(-400,0);
    m_choiceWidget->setVisible(false);

}

void SettingWidget::registL2W(QString WidgetName, QWidget *widget)
{
    L2WTabel.insert(WidgetName,widget);

}

void SettingWidget::setNowLabelPix(QString url)
{
    m_nowLabelPix=url;
}

void SettingWidget::initSettingShowWidget(QString title, QVector<QWidget *> widgets)
{


   // m_settingShowWidget->setStyleSheet("border-image:url(:/UI/RESOURCE/test_transparency2.png);");
    Style::getInstance()->setWidgetBackground(m_settingShowWidget,2);
    m_titleLabel1=new QLabel(this);
    m_titleLabel1->setText(title);
    m_titleLabel1->setFixedSize(1100,250);
    m_titleLabel1->setAlignment(Qt::AlignCenter);
    m_titleLabel1->move(450,0);
    Style::getInstance()->setLabelStyle(m_titleLabel1,4,3);

    for(auto it:widgets)
    {
        QScrollArea * area= new QScrollArea(this);

        m_settingShowWidget->addWidget(area);
        W2ATabel.insert(it,area);
        area->setGeometry(0,0,1200,650);
        // 背景颜色---应该为半透明--等后面来弄
      //  widget->setAutoFillBackground(true);
        //背景颜色---应该为半透明--等后面来弄
        it->setWindowFlags(Qt::FramelessWindowHint);


        area->setWidget(it);
        it->move(0,0);

        area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
}

void SettingWidget::setBackground(QString path)
{
    m_backgroundImage= new QPixmap(path);
}

void SettingWidget::setReturnLabel(JumpLabel *jl)
{
    m_returnLabel=jl;
}

void SettingWidget::changeShowWidget(QWidget * widget)
{

}

bool SettingWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==this && event->type()==QEvent::FocusIn)
    {
        setMouseTracking(true);

    }
    return QWidget::eventFilter(watched,event);
}

void SettingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,width(),height()),*m_backgroundImage);


}

void SettingWidget::hideWidgetAnimated()
{
    m_showStatueTimer->stop();

        // 注释中的代码能实现同样的结果 但是更快地移动。
//    QPropertyAnimation * animation =new QPropertyAnimation(m_choiceWidget,"geomentry");
//    animation->setDuration(500);
//    animation->setStartValue(m_choiceWidget->geometry());

//    QRect endRect =m_choiceWidget->geometry();
//    endRect.moveLeft(-m_choiceWidget->width());
//    animation->setEndValue(endRect);

    QPropertyAnimation * animation =new QPropertyAnimation(m_choiceWidget,"pos");
    animation->setDuration(500);
    QPoint targetPos=QPoint(-m_choiceWidget->width(),0);
    animation->setEndValue(targetPos);

    QObject::connect(animation,&QPropertyAnimation::finished,[this](){
        m_choiceWidget->setVisible(false);
        m_hideStatueTimer->start(100);
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);

}

void SettingWidget::showWidgetAnimated()
{
    m_hideStatueTimer->stop();
    m_choiceWidget->setGeometry(-400,0,400,height());
    m_choiceWidget->setVisible(true);

    QPropertyAnimation *animation= new QPropertyAnimation(m_choiceWidget,"pos");
    animation->setDuration(500);
    QObject::connect(animation,&QPropertyAnimation::finished,[this](){
        m_showStatueTimer->start(100);
    });

    QPoint targetPos=QPoint(0,0);
    animation->setEndValue(targetPos);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}
