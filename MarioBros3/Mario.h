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
	BOOLEAN isOnPlatform;
	BOOLEAN isHolding;
	BOOLEAN isKicking;
	BOOLEAN isTailWhack;
	BOOLEAN isFlying;
	BOOLEAN isRunningFast;
	BOOLEAN startRunning;
	BOOLEAN flickering;

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	ULONGLONG kickTimer;
	ULONGLONG flyTimer;
	ULONGLONG tailTimer;
	ULONGLONG runTimer;
	ULONGLONG untouchable_start;
	ULONGLONG changeFormTimer;

	int coin; 
	int point;
	int level; 
	int untouchable; 
	LPGAMEOBJECT holdingObj;
	LPGAMEOBJECT tail;

	void GetHitFromEnemy();
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithLaser(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	void TailUpdate();
	void HoldingObjUpdate();



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
		startRunning = false;
		isHolding = false;
		isRunningFast = false;
		isFlying = false;
		isOnPlatform = false;
		isKicking = false;
		isTailWhack = false;
		flickering = false;
		flyTimer = 0;
		kickTimer = 0;
		tailTimer = 0;
		runTimer = -1;
		changeFormTimer = 0;
		level = MARIO_LEVEL_SMALL;
		tail = NULL;
		untouchable = 0;
		untouchable_start = -1;
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
		return (isHolding && !holdingObj->IsDeleted());
	}

	int IsBlocking(float nx, float ny) { return (state != MARIO_STATE_DIE && untouchable==0); }

	int IsTanooki() { return (level == MARIO_LEVEL_TANOOKI); }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int GetLevel() { return level; };
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	//void RenderBoundingBox();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};