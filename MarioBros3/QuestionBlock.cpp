#include "QuestionBlock.h"
#include "RewardCoin.h"
#include "Mushroom.h"
#include "SuperLeaf.h"
#include "Mario.h"

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
		//GetReward();
		Scene* current_scene = Game::GetInstance()->GetCurrentScene();
		Mario* mario = dynamic_cast<Mario*>(current_scene->GetPlayer());
		if (mario->GetLevel() == MARIO_LEVEL_BIG && rewardId == ID_REWARD_MUSHROOM)
		{
			rewardId = ID_REWARD_SUPER_LEAF;
			/*this->reward->Delete();
			this->reward = new SuperLeaf(x, y);
			current_scene->AddObject(this->reward);*/
		}
		GetReward();
		vy = RISE_UP_SPEED;
	}
	GameObject::SetState(state);
}
LPGAMEOBJECT QuestionBlock::GetReward()
{
	switch (rewardId)
	{
	case ID_REWARD_COIN:
 		this->reward = new RewardCoin(x, y);
		break;
	case ID_REWARD_MUSHROOM:
		this->reward = new Mushroom(x, y);
		break;
	case ID_REWARD_SUPER_LEAF:
		this->reward = new SuperLeaf(x, y);
		break;
	default:
		break;
	}
	Game::GetInstance()->GetCurrentScene()->AddObject(this->reward);
	return this->reward;
}