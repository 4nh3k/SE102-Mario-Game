#pragma once
#include "GameObject.h"
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

class Card : public GameObject
{
	int cardType;
public:
	Card(float x, float y, int cardType) : GameObject(x,y)
	{
		this->cardType = cardType;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
	void SetCardType(int type)
	{
		this->cardType = type;
	}
	int GetCardType()
	{
		return cardType;
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
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}

};

