#include "style.h"

Style* Style::m_instance = nullptr;

Style* Style::getInstance(QObject *parent)
{
    if (m_instance == nullptr)
    {
        // 在第一次调用时创建唯一实例
        m_instance = new Style(parent);
    }
    return m_instance;
}

Style::Style(QObject *parent)
    : QObject{parent}
    , m_styleName{"Default"}
    , m_btnStyle{"background-color: #F0F0F0; color: #333; border: none; padding: 6px 12px;"}
    , m_primaryLabel{QColor(0, 0, 0)}
    , m_background{QColor(255, 255, 255)}
    , m_icon{QColor(0, 0, 0)}
    , m_textDeep{QColor(51, 51, 51)}
    , m_textShoal{QColor(119, 119, 119)}
    , m_textHighLight{QColor(26, 115, 232)}
    , m_mainLabel{QColor("#F0F0F0")}
{
    // 初始化默认值
}

Style::~Style()
{
    // 删除唯一实例
    m_instance = nullptr;
}

QString Style::styleName() const
{
    return m_styleName;
}

void Style::setStyleName(const QString& styleName)
{
    m_styleName = styleName;
    // 发送信号，通知组件更新样式
    // emit styleChanged();
}

QString Style::btnStyle() const
{
    return m_btnStyle;
}

void Style::setBtnStyle(const QString& btnStyle)
{
    m_btnStyle = btnStyle;
    // 发送信号，通知组件更新样式
  //  emit styleChanged();
}

QColor Style::primaryLabel() const
{
    return m_primaryLabel;
}

void Style::setPrimaryLabel(const QColor& primaryLabel)
{
    m_primaryLabel = primaryLabel;
    // 发送信号，通知组件更新样式
   // emit styleChanged();
}

QColor Style::background() const
{
    return m_background;
}

void Style::setBackground(const QColor& background)
{
    m_background = background;
    // 发送信号，通知组件更新样式
   // emit styleChanged();
}

QColor Style::icon() const
{
    return m_icon;
}

void Style::setIcon(const QColor& icon)
{
    m_icon = icon;
    // 发送信号，通知组件更新样式
    //emit styleChanged();
}

QColor Style::textDeep() const
{
    return m_textDeep;
}

void Style::setTextDeep(const QColor& textDeep)
{
    m_textDeep = textDeep;
    // 发送信号，通知组件更新样式
   // emit styleChanged();
}

QColor Style::textShoal() const
{
    return m_textShoal;
}

void Style::setTextShoal(const QColor& textShoal)
{
    m_textShoal = textShoal;
    // 发送信号，通知组件更新样式
  //  emit styleChanged();
}

QColor Style::textHighLight() const
{
    return m_textHighLight;
}

void Style::setTextHighLight(const QColor& textHighLight)
{
    m_textHighLight = textHighLight;
    // 发送信号，通知组件更新样式
   // emit styleChanged();
}

QColor Style::mainLabel() const
{
    return m_mainLabel;
}

void Style::setMainLabel(const QColor& mainLabel)
{
    m_mainLabel = mainLabel;
    // 发送信号，通知组件更新样式
   // emit styleChanged();
}

void Style::reset(QMap<QString,QString> style)
{
    setStyleName(style.value("StyleName"));
    setBtnStyle(style.value("BtnStyle"));
    setPrimaryLabel(QColor(style.value("PrimaryLabel")));
    setBackground(QColor(style.value("Background")));
    setIcon(QColor(style.value("Icon")));
    setTextDeep(QColor(style.value("TextDeep")));
    setTextShoal(QColor(style.value("TextShoal")));
    setTextHighLight(QColor(style.value("TextHighLight")));
    setMainLabel(QColor(style.value("MainLabel")));
}
