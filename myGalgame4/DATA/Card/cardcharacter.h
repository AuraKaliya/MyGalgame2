#ifndef CARDCHARACTER_H
#define CARDCHARACTER_H

#include "cardbase.h"

#include "../Model/modelbattle.h"
#include "../Model/modelgesture.h"

#include "../Model/modellove.h"
#include "../Model/modelstory.h"


#pragma execution_character_set("utf-8")
class CardCharacter : public CardBase
{
    Q_OBJECT
public:
    CardCharacter();
};

#endif // CARDCHARACTER_H
