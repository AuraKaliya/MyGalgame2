#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget{parent}
{

}

MenuWidget *MenuWidget::m_instance = nullptr;

MenuWidget* MenuWidget::getInstance(QWidget *parent)
{
    if (m_instance == nullptr) {
        m_instance = new MenuWidget(parent);
    }
    return m_instance;
}

void MenuWidget::setBackground(const QPixmap &background)
{
    m_backgroundImage = new QPixmap(background);
//    setAutoFillBackground(true);
//    QPalette pal=this->palette();
//    pal.setBrush(QPalette::Window,
//                 QBrush(m_backgroundImage->scaled(this->size()))
//                 );
//    this->setPalette(pal);

}

void MenuWidget::setTitle(const QPixmap &title, const QString &name,const QPoint &move)
{
    m_tiltleImage = new QPixmap(title);
    m_titleLabel = new QLabel(this);
    m_titleLabel->setMask(m_tiltleImage->mask());
    m_titleLabel->setPixmap(*m_tiltleImage);
    m_titleLabel->move(move);
    qDebug()<<"setTitle";
}

void MenuWidget::setVersion(const QString &version)
{
    m_versionLabel = new QLabel(version, this);
    m_versionLabel->setVisible(false);
//    m_versionLabel->setFixedSize(150, 40);
//    m_versionLabel->setAlignment(Qt::AlignRight);
//    m_versionLabel->move(1085, 690);
}

void MenuWidget::clearJumpGroup()
{
    for (auto &label : m_jumpGroup) {
        delete label;
    }
    m_jumpGroup.clear();
}

void MenuWidget::addJumpLabel(JumpLabel *jumpLabel)
{
    m_jumpGroup.append(jumpLabel);
}

void MenuWidget::customEvent(QEvent *even)
{
//    if(even->type()==QEvent::User)
//    {
//      QCoreApplication::postEvent(parentWidget(), new QEvent(QEvent::User));
//    }

}

void MenuWidget::paintEvent(QPaintEvent *event)
{
//    for(auto it:m_jumpGroup)
//    {
//        it->updatePix();
//    }
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,width(),height()),*m_backgroundImage);
}

void MenuWidget::showEvent(QShowEvent *event)
{
    this->setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(event);
}

void MenuWidget::addLabelInfo(QString text, QPoint pos)
{
    m_labelInfo.append(QPair<QString,QPoint>(text,pos));

}
