#include "cardprop.h"

CardProp::CardProp()
{

    //加载战斗模块

    ModelBase * bt=new ModelBattle();
    model.insert(QString("Battle"),bt);

}
