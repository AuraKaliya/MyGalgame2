#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QVector>
#include "..\UI\jumplabel.h"
#include <QString>
#include <QWidget>
#include <QMap>
#include <QStackedWidget>



class Updater : public QObject
{
    Q_OBJECT
private:
    Updater(QObject* parent = nullptr);
    static Updater* instance;
    QMap<QString,QWidget*> m_widgetTabel;
    QMap <QWidget*,QStackedWidget*> m_parentTabel;
    QVector<JumpLabel*> jumpGroup;

public:
    static Updater* getInstance();

    QWidget* findWidget(QString);
    void registerWidget(QString,QWidget*);

    QStackedWidget* findParent(QWidget*);
    void registerParent(QWidget*,QStackedWidget*);
    void updateJumpLabel();
    void addJumpLabel(JumpLabel*);

signals:
    void jumpLabelsChanged(const QVector<JumpLabel*>&);

private:

};

#endif // UPDATER_H
