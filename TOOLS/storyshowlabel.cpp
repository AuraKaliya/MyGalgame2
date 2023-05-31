#include "storyShowLabel.h"

storyShowLabel::storyShowLabel(QWidget *parent)
    : QLabel(parent), currentIndex(0)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &storyShowLabel::typeNextCharacter);
}

void storyShowLabel::setText(const QString &text)
{
    QLabel::setText(""); // 清空现有文本内容
    originalText = text; // 保存原始文本
    currentIndex = 0; // 初始化当前已显示文本的索引
    timer->start(speed); // 启动打字动画
}

void storyShowLabel::setTypingSpeed(int millisecondsPerCharacter)
{
    speed = millisecondsPerCharacter; // 设置打字速度
}

void storyShowLabel::mousePressEvent(QMouseEvent *event)
{
    if (currentIndex >= originalText.length()) { // 如果已经显示完全
        emit clicked(); // 发送鼠标单击信号
        emit segmentFinished();
    } else { // 如果未显示完全
        timer->stop(); // 暂停打字动画
        QString shownText = originalText; // 直接显示全部文本
        QLabel::setText(shownText);
        currentIndex = originalText.length(); // 更新已显示文本的索引
    }
}

void storyShowLabel::typeNextCharacter()
{
    if (currentIndex >= originalText.length()) { // 如果已经显示完全
        timer->stop(); // 停止定时器
        return;
    }
    QString shownText = originalText.left(currentIndex + 1); // 取得下一个要显示的字符
    QLabel::setText(shownText); // 显示文本
    ++currentIndex; // 更新已显示文本的索引
}
