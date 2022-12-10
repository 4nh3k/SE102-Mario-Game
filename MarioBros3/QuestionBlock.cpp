#include "QuestionBlock.h"
#include "RewardCoin.h"
#include "Mushroom.h"
void QuestionBlock::Render()
{
	Animations* animations = Animations::GetInstance();
	switch (state)
	{
	case QUESTION_BLOCK_STATE_HIT:
		animations->Get(ID_ANI_QUESTION_BLOCK_HIT)->Render(x, y);
		break;
	case QUESTION_BLOCK_STATE_IDLE:
		animations->Get(ID_ANI_QUESTION_BLOCK_IDLE)->Render(x, y);
		break;
	default:
		break;
	}
	RenderBoundingBox();
}
void QuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (y <= oldY - RISE_UP_HEIGH)
	{
		vy = -RISE_UP_SPEED;
	}
	else
	{
		if (y > oldY)
		{
			y = oldY;
			vy = 0;
		}
	}
}
void QuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BLOCK_BBOX_WIDTH / 2;
	t = y - QUESTION_BLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTION_BLOCK_BBOX_WIDTH;
	b = t + QUESTION_BLOCK_BBOX_HEIGHT;
}
void QuestionBlock::SetState(int state)
{
	if (state == QUESTION_BLOCK_STATE_HIT)
	{
		if(dynamic_cast<RewardCoin*>(reward))
			reward->SetSpeed(0.0f, COIN_RISE_UP_SPEED*3);
		else
		{
			reward->SetSpeed(0.0f, MUSHROOM_RAISE_UP_SPEED);
		}
		vy = RISE_UP_SPEED;
	}
	GameObject::SetState(state);
}
LPGAMEOBJECT QuestionBlock::GetReward(int rewardId, int x, int y)
{
	switch (rewardId)
	{
	case ID_REWARD_COIN:
		return new RewardCoin(x, y);
		break;
	case ID_REWARD_MUSHROOM:
		return new Mushroom(x, y);
		break;
	default:
		break;
	}
	return new RewardCoin(x, y);;
}