#include "cardcharacter.h"

CardCharacter::CardCharacter()
{

    //加载战斗、姿态、恋爱、故事表情模块

    ModelBase *bt =new ModelBattle();
    ModelBase *gs =new ModelGesture();
    ModelBase *lv =new ModelLove();
    ModelBase *st =new ModelStory();

   model.insert(QString("Battle"),bt);
   model.insert(QString("Gesture"),gs);
   model.insert(QString("Love"),lv);
   model.insert(QString("Story"),st);

}
