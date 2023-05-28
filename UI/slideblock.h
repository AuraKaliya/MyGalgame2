#ifndef SLIDEBLOCK_H
#define SLIDEBLOCK_H

#include <QPushButton>
#include <QObject>
#include <QRect>
#include <QMouseEvent>


class SlideBlock : public QPushButton
{
    Q_OBJECT
public:
    SlideBlock();
    void setRect(QRect rect);
    void mousePressEvent(QMouseEvent * e)override;
    void mouseMoveEvent(QMouseEvent *e)override;
    void mouseReleaseEvent(QMouseEvent * e) override;
    void initPos();
    void resetPos();
    void setMouseStartPos(QPoint newMouseStartPos);

    void setFixPos(QPoint newFixPos);

signals:
    void valueMax();
    void reset();
private:
    QRect m_abRect;
    QPoint m_mouseStartPos;
    QPoint fixPos;
    QPoint m_btnStarPos;
    int values;
    bool m_isPressed;

};

#endif // SLIDEBLOCK_H
