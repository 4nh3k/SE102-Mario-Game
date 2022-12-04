#pragma once
#include "Coin.h"
#define REWARD_COIN_ANI_ID "coin_rotate"
#define RISE_UP_HEIGH 48
class RewardCoin :
    public Coin
{
	float oldY;

public:
	RewardCoin(float x, float y) : Coin(x, y) {
		oldY = y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Delete() { isDeleted = true; }
	int IsBlocking(float nx, float ny) { return 0; }
};

