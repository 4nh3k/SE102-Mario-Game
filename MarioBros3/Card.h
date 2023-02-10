#pragma once
#include "Animations.h"

#define CARD_FLOWER_ID	0
#define CARD_STAR_ID	1
#define CARD_MUSHROOM_ID	2

#define CARD_WIDTH 24
#define CARD_HEIGHT 28

#define ANI_ID_FLOWER_CARD "flower_card"

class Card
{
	float x, y;
public:
	Card(float x, float y, int cardType)
	{
		this->x = x;
		this->y = y;
	}
	void SetPos(float x, float y) { this->x = x; this->y = y; }
	void SetNumber(int num);
	void Render()
	{
		Animations::GetInstance()->Get(ANI_ID_FLOWER_CARD)->Render(x, y);
	}
};

