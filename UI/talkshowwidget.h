#ifndef TALKSHOWWIDGET_H
#define TALKSHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include "jumplabel.h"
#include "../TOOLS/storyshowlabel.h"
#include "style.h"
#include "uiwidget.h"
class TalkShowWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit TalkShowWidget(QWidget *parent = nullptr);
    void initToolLabelGroup(QVector<JumpLabel*>jpG);
    void setText(QString text);
    void setHead(QPixmap headPix);
    void setToolPix(QPixmap pix);
   storyShowLabel *getStoryShowLabel() const;

private:
    QLabel *m_headLabel;
    storyShowLabel * m_storyShowLabel;
    QVector <JumpLabel*> m_toolLabelGroup;
    QLabel * m_toolLabel;
};

#endif // TALKSHOWWIDGET_H
