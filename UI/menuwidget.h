#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPixmap>
#include <QLabel>
#include "jumplabel.h"
#include <QEvent>
#include<QCoreApplication>
#include <QBrush>
#include <QPainter>

#pragma execution_character_set("utf-8")
class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    static MenuWidget *getInstance(QWidget *parent = nullptr);

    void setBackground(const QPixmap &background);
    void setTitle(const QPixmap &title, const QString &name,const QPoint &move);
    void setVersion(const QString &version);
    void clearJumpGroup();
    void addJumpLabel(JumpLabel *jumpLabel);
    void customEvent(QEvent * even) override;
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent *event) override;
    void addLabelInfo(QString text,QPoint pos);

private:
    explicit MenuWidget(QWidget *parent = nullptr);
    static MenuWidget *m_instance;

    QVector<JumpLabel*> m_jumpGroup;
    QPixmap *m_backgroundImage;
    QPixmap *m_tiltleImage;
    QLabel * m_titleLabel;
    QLabel * m_versionLabel;

    QVector<QPair<QString,QPoint>> m_labelInfo;


signals:

};

#endif // MENUWIDGET_H
