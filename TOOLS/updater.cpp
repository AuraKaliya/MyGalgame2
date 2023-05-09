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

void Updater::updateJumpLabel()
{
    for(auto it:jumpGroup)
        it->updatePix();


    qDebug()<<"updateJumpLabel";
}

void Updater::addJumpLabel(JumpLabel* label)
{
    jumpGroup.append(label);
    emit jumpLabelsChanged(jumpGroup);
}
