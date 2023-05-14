#include "updater.h"

Updater* Updater::instance = nullptr;

Updater::Updater(QObject* parent)
    : QObject(parent)
{
}

Updater* Updater::getInstance()
{
    if (instance == nullptr) {
        instance = new Updater();
    }
    return instance;
}

QWidget *Updater::findWidget(QString name)
{
    return m_widgetTabel.value(name);
}

void Updater::registerWidget(QString name, QWidget * widget)
{
    m_widgetTabel.insert(name,widget);
}

QStackedWidget *Updater::findParent(QWidget *w)
{
 return m_parentTabel.value(w);
}

void Updater::registerParent(QWidget *w, QStackedWidget *sw)
{
    m_parentTabel.insert(w,sw);
}

void Updater::updateJumpLabel()
{
    for(auto it:jumpGroup)
        it->updatePix();


 //   qDebug()<<"updateJumpLabel";
}

void Updater::addJumpLabel(JumpLabel* label)
{
    jumpGroup.append(label);
    emit jumpLabelsChanged(jumpGroup);
}
