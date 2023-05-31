#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>

class TachieLabel;
class TalkShowWidget;
class UIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UIWidget(QWidget *parent = nullptr);
    virtual void setBackgroundPixUrl(QString){};          //规定传入的统一为QString
    virtual void setStyle(QString){};
    virtual void setBackgroundMusicUrl(QString){};
    virtual void initTachieLabel(TachieLabel* tl,QRect rect){};
    virtual void initTalkShowWidget(TalkShowWidget*tl,QRect rect){};
signals:

};

#endif // UIWIDGET_H
