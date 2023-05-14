#ifndef RSWIDGET_H
#define RSWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QString>

#include "../TOOLS/updater.h"
#include "jumplabel.h"
#include "chievementwidget.h"

class RSWidget : public QWidget
{
    Q_OBJECT
private:
    static RSWidget* instance;
    RSWidget(QWidget *parent = nullptr);
    ~RSWidget();



    QScrollArea * m_showArea;
    QWidget *m_showWidget;
    int m_count;
    JumpLabel * addLabel;



public:
    static RSWidget* getInstance(QWidget *parent = nullptr);
    void addAchWidget(chievementWidget* achWidget);
    void initAddLabel(QString normalUrl,QString PressUrl);
public slots:
    void showNewAchWidget();

signals:

};

#endif // RSWIDGET_H
