#pragma once
#include "GameObject.h"

#define ID_ANI_QUESTION_BLOCK_IDLE "question_block_idle"
#define ID_ANI_QUESTION_BLOCK_HIT "question_block_hit"
#define QUESTION_BLOCK_BBOX_WIDTH 16
#define QUESTION_BLOCK_BBOX_HEIGHT 16
#define RISE_UP_HEIGH 2
#define RISE_UP_SPEED -0.08f

#define ID_REWARD_COIN 0
#define ID_REWARD_MUSHROOM 1
#define ID_REWARD_SUPER_LEAF 2
#define ID_REWARD_1UP_MUSHROOM 3
#define ID_REWARD_PSWITCH 4


#define QUESTION_BLOCK_STATE_IDLE 10
#define QUESTION_BLOCK_STATE_HIT 20

class QuestionBlock : public GameObject
{
	float oldY;
	LPGAMEOBJECT reward;
	int rewardId;
public:
	QuestionBlock(float x, float y, int rewardId) : GameObject(x, y) {
		oldY = y;
		this->reward = NULL;
		this->rewardId = rewardId;
		state = QUESTION_BLOCK_STATE_IDLE;
		//GetReward();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	LPGAMEOBJECT GetReward();
	void SetState(int state);
};

