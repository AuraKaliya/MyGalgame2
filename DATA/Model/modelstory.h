#ifndef MODELSTORY_H
#define MODELSTORY_H

#include "modelbase.h"

#pragma execution_character_set("utf-8")
class ModelStory:public ModelBase
{
public:
    ModelStory();


private:
      /**已有继承的表为（正常 开心 害羞 生气 惊讶）X(ImageUrl)**/
    /**剧情模块对应表情系统 固定 0 正常 1 开心 2 害羞 3 生气 4 惊讶 **/
};

#endif // MODELSTORY_H
