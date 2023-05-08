#include "JumpLabel.h"
#include <QMouseEvent>

JumpLabel::JumpLabel(QWidget* parent)
    : QLabel(parent)
    , m_DestinationWidget(nullptr)
    , m_NormalPix(nullptr)
    , m_PressPix(nullptr)
{
    // 默认不启用遮罩效果
    m_MaskStatus=false;
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
    setPixmap(m_NormalPix->scaled(width(),height()));
}

// 设置是否启用遮罩效果
void JumpLabel::setMaskStatus(bool flag)
{
    // 记录是否启用遮罩效果的标志
    m_MaskStatus=flag;
    // 如果启用，并且正常状态下和被按下状态下的图片都不为空
    if(m_MaskStatus&&(!m_NormalPix->isNull())&&(!m_PressPix->isNull()))
    {
        // 将标签设置为带遮罩的样式
        setMask(m_NormalPix->mask());
    }
}

// 鼠标按下事件
void JumpLabel::mousePressEvent(QMouseEvent* event)
{
    if (m_PressPix) {
        // 设置标签的图片为被按下状态下的图片
        if(m_MaskStatus){
            setMask(m_PressPix->mask());
        }
        setPixmap(m_PressPix->scaled(width(),height()));
    }

    if (event->button() == Qt::LeftButton && event->type() == QEvent::MouseButtonRelease) {
        // 发送无参数的点击信号
        emit clicked();

        if (m_DestinationWidget) {
            // 发送带一个参数指向目标窗体的点击信号
            emit clicked(m_DestinationWidget);
        }
    }

    QLabel::mousePressEvent(event);
}

// 鼠标释放事件
void JumpLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_NormalPix) {
        // 设置标签的图片为正常状态下的图片
        if(m_MaskStatus){
            setMask(m_NormalPix->mask());
        }

        setPixmap(m_NormalPix->scaled(width(),height()));
    }

    QLabel::mouseReleaseEvent(event);
}
