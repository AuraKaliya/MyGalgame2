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
    void setTitle(const QPixmap &title, const QString &name);
    void setVersion(const QString &version);
    void clearJumpGroup();
    void addJumpLabel(JumpLabel *jumpLabel);
    void customEvent(QEvent * even) override;
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent *event) override;
    QVector<JumpLabel*> m_jumpGroup;
private:
    explicit MenuWidget(QWidget *parent = nullptr);
    static MenuWidget *m_instance;


    QPixmap *m_backgroundImage;

    QPixmap *m_tiltleImage;
    QLabel * m_titleLabel;

    QLabel * m_versionLabel;

signals:

};

#endif // MENUWIDGET_H
