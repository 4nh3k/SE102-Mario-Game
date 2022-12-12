#pragma once
#include "Coin.h"
#define REWARD_COIN_ANI_ID "reward_coin"
#define COIN_RISE_UP_HEIGH 48
#define COIN_RISE_UP_SPEED -0.2f
class RewardCoin :
    public Coin
{
	float oldY;

public:
	RewardCoin(float x, float y) : Coin(x, y) {
		vy = COIN_RISE_UP_SPEED;
		oldY = y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Delete() { isDeleted = true; }
	int IsBlocking(float nx, float ny) { return 0; }
};

