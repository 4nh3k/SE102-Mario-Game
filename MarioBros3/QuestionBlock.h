#pragma once
#include "GameObject.h"

#define ID_ANI_QUESTION_BLOCK_IDLE "question_block_idle"
#define ID_ANI_QUESTION_BLOCK_HIT "question_block_hit"
#define QUESTION_BLOCK_BBOX_WIDTH 16
#define QUESTION_BLOCK_BBOX_HEIGHT 16
#define RISE_UP_HEIGH 3
#define RISE_UP_SPEED -0.08f

#define ID_REWARD_COIN 0
#define ID_REWARD_MUSHROOM 1

#define QUESTION_BLOCK_STATE_IDLE 10
#define QUESTION_BLOCK_STATE_HIT 20

class QuestionBlock : public GameObject
{
	float oldY;
	LPGAMEOBJECT reward;
public:
	QuestionBlock(float x, float y, LPGAMEOBJECT reward) : GameObject(x, y) {
		oldY = y;
		this->reward = reward;
		state = QUESTION_BLOCK_STATE_IDLE;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	static LPGAMEOBJECT GetReward(int rewardId, int x, int y);

	void SetState(int state);
};

