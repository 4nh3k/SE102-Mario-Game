#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "QuestionBlock.h"
#include "debug.h"
#include "Tail.h"
#include "MarioConst.h"
#include "PointSFX.h"


class Mario : public GameObject
{
	BOOLEAN isSitting;
	BOOLEAN isOnPlatform;
	BOOLEAN isHolding;
	BOOLEAN isKicking;
	BOOLEAN isTailWhack;
	BOOLEAN isFlying;
	BOOLEAN isRunningFast;
	BOOLEAN flickering;
	BOOLEAN isPressUp;
	BOOLEAN hasFinish;
	BOOLEAN teleporting;

	int teleDirection;
	float oldY;
	float teleX;
	float teleY;
	float teleCamX;
	float teleCamY;

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	ULONGLONG kickTimer;
	ULONGLONG flyTimer;
	ULONGLONG tailTimer;
	ULONGLONG runTimer;
	ULONGLONG deadTimer;
	ULONGLONG untouchable_start;
	ULONGLONG changeFormTimer;

	int combo;
	int level; 
	int preLevel;
	int untouchable; 

	LPGAMEOBJECT holdingObj;
	LPGAMEOBJECT tail;

	void GetHitFromEnemy();
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithParaKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithLaser(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithPSwitch(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoal(LPCOLLISIONEVENT e);
	void OnCollisionWithTheVoid(LPCOLLISIONEVENT e);
	void OnCollisionWithPipeline(LPCOLLISIONEVENT e);

	void TailUpdate();
	void HoldingObjUpdate();


	string GetAniIdBig();
	string GetAniIdSmall();
	string GetAniIdTanooki();
public:
	Mario(float x, float y);
	BOOLEAN IsHolding();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetLevel(int l);
	void SetUpKey(bool);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void AddScore(float Px, float Py);
	void AddScore(float Px, float Py, int point);
	void AddCoin();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	BOOLEAN IsGoingPipeLine();
	BOOLEAN HasFinish();
	int IsCollidable();
	int IsBlocking(float nx, float ny);
	int IsTanooki();
	int IsFlying();
	int IsOnPlatform();
	int GetLevel();
	int CalcPoint(int combo);
};