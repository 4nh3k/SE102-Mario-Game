#include "RewardCoin.h"

void RewardCoin::Render()
{
	Animations* animations = Animations::GetInstance();
	switch (state)
	{
		animations->Get(REWARD_COIN_ANI_ID)->Render(x,y);
	}
	animations->Get(REWARD_COIN_ANI_ID)->Render(x, y);

	//RenderBoundingBox();
}
void RewardCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (y <= oldY - COIN_RISE_UP_HEIGH)
	{
		vy = -COIN_RISE_UP_SPEED;
	}
	else
	{
		if (y > oldY )
		{
			this->Delete();
			//y = oldY;
			vy = 0;
		}
	}
}

