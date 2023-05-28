#ifndef JUMPLABEL_H
#define JUMPLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QCoreApplication>

class JumpLabel : public QLabel
{
    Q_OBJECT

public:
    // 构造函数，parent为父控件，默认为nullptr
    JumpLabel(QWidget* parent = nullptr);
    // 设置跳转窗体的指针
    void setDestination(QWidget* destination);
    // 设置正常状态和被按下状态下的图片
    void setPixmapGroup(QPixmap* normal, QPixmap* press);
    void setPixmapPathGroup(QString normal,QString press);
    // 设置是否启用遮罩效果
    void setMaskStatus(bool flag);
    bool isPressed();
    bool hasFocused();
    void updatePix();
    void changePix();

    int getCardID() const;
    void setCardID(int newCardID);

signals:
    // 点击信号，无参数
    void clicked();
    // 点击信号，带一个参数指向目标窗体
    // void clicked(QWidget* destination);
    void jump(QWidget* destination);
    void choiceCard(int id);

protected:
    // 鼠标按下事件
    void mousePressEvent(QMouseEvent* event) override;
    // 鼠标释放事件
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    // 目标窗体指针
    QWidget* m_DestinationWidget;

    //
    QString m_NormalPixPath;
    QString m_PressPixPath;
    QString m_NowPixPath;
    QString m_NextPixPath;
    // 正常状态下的图片指针
    QPixmap* m_NormalPix;
    // 被按下状态下的图片指针
    QPixmap* m_PressPix;

    // 是否启用遮罩效果的标志
    int cardID;
    bool isPress;
    bool focuse;
    bool m_MaskStatus;

};


#endif // JUMPLABEL_H
