#pragma once
#include "GameObject.h"

#define ID_ANI_QUESTION_BLOCK_IDLE "question_block_idle"
#define ID_ANI_QUESTION_BLOCK_HIT "question_block_hit"
#define QUESTION_BLOCK_BBOX_WIDTH 16
#define QUESTION_BLOCK_BBOX_HEIGHT 16
#define RISE_UP_HEIGH 5
#define RISE_UP_SPEED -0.1f

#define QUESTION_BLOCK_STATE_IDLE 1
#define QUESTION_BLOCK_STATE_HIT 2

class QuestionBlock : public GameObject
{
	float oldY;
	LPGAMEOBJECT reward;
public:
	QuestionBlock(float x, float y, LPGAMEOBJECT reward) : GameObject(x, y) {
		this->reward = reward;
		state = QUESTION_BLOCK_STATE_IDLE;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state) {
		if (state == QUESTION_BLOCK_STATE_HIT)
		{
			reward->SetSpeed(0.05f, RISE_UP_SPEED/2);
			oldY = y;
			vy = RISE_UP_SPEED;
		}
		GameObject::SetState(state);
	}
};

