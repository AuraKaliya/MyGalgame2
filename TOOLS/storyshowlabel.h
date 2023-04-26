#ifndef STORY_SHOW_LABEL_H
#define STORY_SHOW_LABEL_H

#include <QLabel>
#include <QTimer>
#include <QMouseEvent>

class storyShowLabel : public QLabel // 继承自QLabel
{
    Q_OBJECT // 用于信号槽机制的宏

public:
    explicit storyShowLabel(QWidget *parent = nullptr); // 构造函数
    void setText(const QString &text); // 重写setText函数
    void setTypingSpeed(int millisecondsPerCharacter); // 设置打字速度

signals:
    void clicked(); // 定义鼠标单击信号

protected:
    void mousePressEvent(QMouseEvent *event) override; // 鼠标按下事件

private slots:
    void typeNextCharacter(); // 打字动画

private:
    QString originalText; // 原始文本内容
    QTimer *timer; // 定时器，用于打字动画
    int speed = 50; // 默认打字速度，单位为毫秒每个字符
    int currentIndex; // 当前已显示的文本字符索引
};

#endif // STORY_SHOW_LABEL_H
