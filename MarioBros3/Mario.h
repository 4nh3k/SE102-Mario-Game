#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "QuestionBlock.h"
#include "debug.h"
#include "Tail.h"
#include "MarioConst.h"


class Mario : public GameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	ULONGLONG kickTimer;
	ULONGLONG flyTimer;
	ULONGLONG tailTimer;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	BOOLEAN isHolding;
	BOOLEAN isFlying;
	GameObject* holdingObj;
	LPGAMEOBJECT tail;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e);

	string GetAniIdBig();
	string GetAniIdSmall();
	string GetAniIdTanooki();
public:
	Mario(float x, float y) : GameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		holdingObj = NULL;
		isHolding = false;
		isFlying = false;
		flyTimer = 0;
		kickTimer = 0;
		tailTimer = 0;
		level = MARIO_LEVEL_BIG;
		tail = NULL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	BOOLEAN IsHolding()
	{
		return isHolding;
	}

	int IsBlocking(float nx, float ny) { return (state != MARIO_STATE_DIE && untouchable==0); }

	int IsTanooki() { return (level == MARIO_LEVEL_TANOOKI); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int GetLevel() { return level; };
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void RenderBoundingBox();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};