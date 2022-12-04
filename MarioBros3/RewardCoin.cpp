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
	x += vx * dt;
	y += vy * dt;
	if (y < oldY - RISE_UP_HEIGH)
	{
		vy = -vy;
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

