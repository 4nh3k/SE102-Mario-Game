#include "RewardCoin.h"
#include "Mario.h"

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
		if (y > oldY - COIN_DELETE_HEIGHT && vy >=0 )
		{
			if (!this->IsDeleted())
			{	
				LPGAMEOBJECT player = Game::GetInstance()->GetCurrentScene()->GetPlayer();
				Mario* mario = dynamic_cast<Mario*>(player);
				mario->AddCoin();
				mario->AddScore(x,y,100);
			}
			this->Delete();
			//y = oldY;
			vy = 0;
		}
	}
}

