#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QVector>

#include "..\UI\jumplabel.h"

class Updater : public QObject
{
    Q_OBJECT
private:
    Updater(QObject* parent = nullptr);
    static Updater* instance;

public:
    static Updater* getInstance();
    void updateJumpLabel();
    void addJumpLabel(JumpLabel*);
   QVector<JumpLabel*> jumpGroup;
signals:
    void jumpLabelsChanged(const QVector<JumpLabel*>&);

private:

};

#endif // UPDATER_H
