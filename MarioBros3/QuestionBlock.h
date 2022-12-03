#pragma once
#include "GameObject.h"

#define ID_ANI_QUESTION_BLOCK_IDLE "question_block_idle"
#define ID_ANI_QUESTION_BLOCK_HIT "question_block_hit"
#define QUESTION_BLOCK_BBOX_WIDTH 16
#define QUESTION_BLOCK_BBOX_HEIGHT 16

#define QUESTION_BLOCK_STATE_IDLE 1
#define QUESTION_BLOCK_STATE_HIT 2

class QuestionBlock : public GameObject
{
public:
	QuestionBlock(float x, float y) : GameObject(x, y) {
		state = QUESTION_BLOCK_STATE_IDLE;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state) {
		GameObject::SetState(state);
	}
};

