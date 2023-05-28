#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <QVector>
#include <QPixmap>
#include <QRect>
#include <QPushButton>
#include <QPainter>
#include <QPropertyAnimation>

#include "jumplabel.h"
#include "headwidget.h"
#include "tachielabel.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    static MainWidget* getInstance(QWidget *parent = nullptr);
    void initMainShowLabel(QVector<JumpLabel*>label,QVector<QRect> rect);
    void initToolShowLabel(QVector<JumpLabel*>label,QVector<QRect> rect);
    void initToolButton(QPixmap pix,QString pixPath);
    void initToolButton(QPixmap maskPix,QString pixPathHide,QString pixPathShow);
    void initTachieLabel(TachieLabel* tachieLabel,QRect rect);
    void setHeadWidget(HeadWidget*head,QRect rect);
    void setBackground(QString bkgPath);


    void paintEvent(QPaintEvent *e)override;


public slots:
    void showToolList();
    void hideToolList();
private:
    MainWidget(QWidget *parent = nullptr);
    static MainWidget* m_instance;
    QVector<JumpLabel*> m_mainShowLabelGroup;
    QPushButton * m_toolShowButton;
    bool buttonStautes;
    QString hidePixPath;
    QString showPixPath;

    TachieLabel* m_tachieLabel;

    QVector<JumpLabel*> m_toolShowLabelGroup;
    HeadWidget* m_head;

    QPixmap * m_backgroundImage;


signals:

};
#endif // MAINWIDGET_H
