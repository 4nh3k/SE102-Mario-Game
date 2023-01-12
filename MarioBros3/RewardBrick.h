#pragma once
#include "QuestionBlock.h"

#define ID_ANI_BRICK "brick"

class RewardBrick : public QuestionBlock
{
public:
	RewardBrick(float x, float y, int rewardId) : QuestionBlock(x, y, rewardId) {}
	void Render()
	{
		Animations* animations = Animations::GetInstance();
		switch (state)
		{
		case QUESTION_BLOCK_STATE_HIT:
			animations->Get(ID_ANI_QUESTION_BLOCK_HIT)->Render(x, y);
			break;
		case QUESTION_BLOCK_STATE_IDLE:
			animations->Get(ID_ANI_BRICK)->Render(x, y, false);
			break;
		default:
			break;
		}
		//RenderBoundingBox();

	}
};

