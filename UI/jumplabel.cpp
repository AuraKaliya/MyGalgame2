#include "JumpLabel.h"
#include <QMouseEvent>

JumpLabel::JumpLabel(QWidget* parent)
    : QLabel(parent)
    , m_DestinationWidget(nullptr)
    , m_NormalPix(nullptr)
    , m_PressPix(nullptr)
{
    m_NormalPixPath="";
    // 默认不启用遮罩效果
    m_MaskStatus=false;
    setScaledContents(true);
    isPress=false;
    focuse = false;
    cardID=0;
}

// 设置跳转窗体的指针
void JumpLabel::setDestination(QWidget* destination)
{
    m_DestinationWidget = destination;
}

// 设置正常状态和被按下状态下的图片
void JumpLabel::setPixmapGroup(QPixmap* normal, QPixmap* press)
{
    // 记录正常状态下的图片指针
    m_NormalPix = normal;
    // 记录被按下状态下的图片指针
    m_PressPix = press;
    // 设置标签的图片为正常状态下的图片
    //  setPixmap(m_NormalPix->scaled(width(),height()));

    setStyleSheet("border-image:url("+m_NormalPixPath+");");
}

void JumpLabel::setPixmapPathGroup(QString normal, QString press)
{
    m_NormalPixPath=normal;
    m_PressPixPath=press;
    setStyleSheet("border-image:url("+m_NormalPixPath+");");
    m_NowPixPath=m_NormalPixPath;
    m_NextPixPath=m_PressPixPath;
}

// 设置是否启用遮罩效果
void JumpLabel::setMaskStatus(bool flag)
{
    qDebug()<<"setMask:"<<flag;
    // 记录是否启用遮罩效果的标志
    m_MaskStatus=flag;
    // 如果启用，并且正常状态下和被按下状态下的图片都不为空
    if(m_MaskStatus&&(!m_NormalPix->isNull())&&(!m_PressPix->isNull()))
    {
        // 将标签设置为带遮罩的样式
        setMask(m_NormalPix->mask());
    }
}

bool JumpLabel::isPressed()
{
    return isPress;
}

bool JumpLabel::hasFocused()
{
    return focuse;
}

void JumpLabel::updatePix()
{


    if(!m_PressPixPath.isEmpty()&&!m_NormalPixPath.isEmpty())
    {
    if(isPress)
    {
       // setPixmap(m_PressPix->scaled(width(),height()));
        setStyleSheet("border-image:url("+m_PressPixPath+");");
       m_NowPixPath=m_PressPixPath;
        m_NextPixPath=m_NormalPixPath;
      // qDebug()<<"updatePix:Press";

    }else {
        // setPixmap(m_NormalPix->scaled(width(),height()));
        setStyleSheet("border-image:url("+m_NormalPixPath+");");
       m_NowPixPath=m_NormalPixPath;
        m_NextPixPath=m_PressPixPath;
      // qDebug()<<"updatePix:Normal";
    }
    }
}

void JumpLabel::changePix()
{
    setStyleSheet("border-image:url("+m_NextPixPath+");");
    QString tmpPath=m_NowPixPath;
    m_NowPixPath=m_NextPixPath;
    m_NextPixPath=tmpPath;
}

// 鼠标按下事件
void JumpLabel::mousePressEvent(QMouseEvent* event)
{
   // qDebug()<<"mousePressEvent";

    if (m_PressPix) {
        // 设置标签的图片为被按下状态下的图片
        if(m_MaskStatus){
            setMask(m_PressPix->mask());

        }
        isPress=true;
       // setPixmap(m_PressPix->scaled(width(),height()));

    }
    emit me(this);
    QCoreApplication::postEvent(parentWidget(), new QEvent(QEvent::User));
    QLabel::mousePressEvent(event);
}

// 鼠标释放事件
void JumpLabel::mouseReleaseEvent(QMouseEvent* event)
{
    isPress=false;
    if (m_NormalPix) {
        // 设置标签的图片为正常状态下的图片
        if(m_MaskStatus){
            setMask(m_NormalPix->mask());
        }
        // setPixmap(m_NormalPix->scaled(width(),height()));
    }
    // QCoreApplication::postEvent(parentWidget(), new QEvent(QEvent::User));

    if (event->button() == Qt::LeftButton ) {
        // 发送无参数的点击信号
        qDebug()<<"clicked";
        emit clicked();
       // qDebug()<<"clicked solve";
        // emit  jump(m_DestinationWidget);
        if(cardID!=0)
        {
            emit choiceCard(cardID);
        }

        if (m_DestinationWidget) {
            // 发送带一个参数指向目标窗体的点击信号
            //  emit clicked(m_DestinationWidget);
            focuse=!focuse;
            qDebug()<<"m_DestinationWidget:"<<m_DestinationWidget;
            emit  jump(m_DestinationWidget);
        }
    }

    QLabel::mouseReleaseEvent(event);
}

int JumpLabel::getCardID() const
{
    return cardID;
}

void JumpLabel::setCardID(int newCardID)
{
    cardID = newCardID;
}

void JumpLabel::showInfo()
{
    qDebug()<<"__________";
    qDebug()<<"isVisible:"<<isVisible();
    qDebug()<<"Url:"<<m_PressPixPath<<"   "<<m_NormalPixPath;
    qDebug()<<"Geo"<<geometry() <<"ID:"<<cardID;
    qDebug()<<"__________";

}
