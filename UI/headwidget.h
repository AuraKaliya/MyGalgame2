#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QWidget>
#include "jumplabel.h"
#include <QLabel>
#include <QPixmap>

class HeadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HeadWidget(QWidget *parent = nullptr);
    HeadWidget* show(QWidget*parent) const;

    void initPix(QPixmap*head,QPixmap * infoLabel);
    void setFrame(QPixmap*framePix);
    void initInfoText(QString RSID,QString StoryProgress);


    QLabel *SRIDLabel() const;
    QLabel *StoryProgressLabel() const;

private:
    JumpLabel * m_headLabel;
    QLabel * m_infoLabel;
    QLabel * m_frameLabel;
    QLabel * m_SRIDLabel;
    QLabel * m_StoryProgressLabel;

signals:

};

#endif // HEADWIDGET_H
