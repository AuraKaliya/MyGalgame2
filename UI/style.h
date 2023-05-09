#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QMap>
#include <QColor>

class Style : public QObject
{
    Q_OBJECT
public:
    // 获取Style实例
    static Style* getInstance(QObject *parent = nullptr);
    void reset(QMap<QString,QString> style);
    // 获取/设置组件风格名称
    QString styleName() const;
    void setStyleName(const QString& styleName);

    // 获取/设置按钮样式
    QString btnStyle() const;
    void setBtnStyle(const QString& btnStyle);

    // 获取/设置主要标签颜色
    QColor primaryLabel() const;
    void setPrimaryLabel(const QColor& primaryLabel);

    // 获取/设置背景颜色
    QColor background() const;
    void setBackground(const QColor& background);

    // 获取/设置图标颜色
    QColor icon() const;
    void setIcon(const QColor& icon);

    // 获取/设置深色文本颜色
    QColor textDeep() const;
    void setTextDeep(const QColor& textDeep);

    // 获取/设置浅色文本颜色
    QColor textShoal() const;
    void setTextShoal(const QColor& textShoal);

    // 获取/设置高亮文本颜色
    QColor textHighLight() const;
    void setTextHighLight(const QColor& textHighLight);

    // 获取/设置主标签颜色
    QColor mainLabel() const;
    void setMainLabel(const QColor& mainLabel);
signals:
    void styleChanged();

private:
    explicit Style(QObject *parent = nullptr);
    ~Style();

    // 静态成员变量，用于存储唯一实例
    static Style* m_instance;

    // 私有化拷贝构造函数和赋值运算符
    Style(const Style&) = delete;
    Style& operator=(const Style&) = delete;

    // 成员变量
    QString   m_styleName;
    QString   m_btnStyle;
    QColor    m_primaryLabel;
    QColor    m_background;
    QColor    m_icon;
    QColor    m_textDeep;
    QColor    m_textShoal;
    QColor    m_textHighLight;
    QColor    m_mainLabel;

};

#endif // STYLE_H
