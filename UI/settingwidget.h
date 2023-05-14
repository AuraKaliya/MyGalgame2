#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include "jumplabel.h"
#include <QWidget>
#include <QStackedWidget>
#include <QVector>
#include <QTimer>
#include <QPoint>
#include <QEvent>
#include <QPixmap>
#include <QFont>
#include <QPropertyAnimation>
#include <QMap>
#include <QScrollArea>
#include <QPainter>

#include "style.h"


class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    static SettingWidget* getInstance(QWidget *parent = nullptr);

    bool checkedShow();
    bool checkedHide();
    void initChoiceWidget(QString title,QVector<JumpLabel*>labelGroup,QString choicePix="");
    void registL2W(QString WidgetName,QWidget* widget);
    void setNowLabelPix(QString url);
    void initSettingShowWidget(QString title,QVector<QWidget*>widgets);
    void setBackground(QString path);
    void setReturnLabel(JumpLabel*);

public slots:
    void changeShowWidget(QWidget* widget);
protected:
    bool eventFilter(QObject *watched,QEvent *event) override;
    void paintEvent(QPaintEvent *event)override;

private:
    static SettingWidget* m_instance;
    explicit SettingWidget(QWidget *parent = nullptr);

    QWidget *m_choiceWidget;
    QLabel *m_titleLabel1;
    QLabel *m_titleLabel2;
    QLabel *m_choiceIconLabel;
    QMap<QString,QWidget*> L2WTabel;
    QMap<QWidget*,QScrollArea*> W2ATabel;

    QStackedWidget *m_settingShowWidget;


    QPixmap *m_backgroundImage;

    JumpLabel *m_nowLabel;
    QString m_nowLabelPix;
    bool m_trackingMouse=false;
    QTimer *m_hideStatueTimer;
    QTimer *m_showStatueTimer;

    JumpLabel *m_returnLabel;

    void hideWidgetAnimated();
    void showWidgetAnimated();

signals:

};

#endif // SETTINGWIDGET_H
