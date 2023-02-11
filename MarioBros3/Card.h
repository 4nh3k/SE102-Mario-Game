#pragma once
#include "Animations.h"

#define CARD_EMPTY_ID -1
#define CARD_FLOWER_ID	0
#define CARD_STAR_ID	1
#define CARD_MUSHROOM_ID	2

#define CARD_WIDTH 24
#define CARD_HEIGHT 28

#define ANI_ID_EMPTY_CARD "empty_card"
#define ANI_ID_FLOWER_CARD "flower_card"
#define ANI_ID_STAR_CARD "star_card"
#define ANI_ID_MUSHROOM_CARD "mushroom_card"

class Card
{
	int cardType;
	float x, y;
public:
	Card(float x, float y, int cardType)
	{
		this->x = x;
		this->y = y;
		this->cardType = cardType;
	}
	void SetPos(float x, float y) { this->x = x; this->y = y; }
	void SetCardType(int type)
	{
		this->cardType = type;
	}
	void Render()
	{
		string aniId = ANI_ID_EMPTY_CARD;
		switch (cardType)
		{
		case 0:
			aniId = ANI_ID_FLOWER_CARD;
			break;
		case 1:
			aniId = ANI_ID_STAR_CARD;
			break;
		case 2:
			aniId = ANI_ID_MUSHROOM_CARD;
			break;
		default:
			break;
		}
		Animations::GetInstance()->Get(aniId)->Render(x, y);
	}
};

