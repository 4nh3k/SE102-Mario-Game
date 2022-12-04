#include "QuestionBlock.h"
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
	if (y < oldY - RISE_UP_HEIGH)
	{
		vy = -vy;
	}
	else
	{
		if (y >= oldY)
		{
			//y = oldY;
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