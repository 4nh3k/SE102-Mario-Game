#pragma once
#include "GameObject.h"

#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_KICKED_SPEED 0.2f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_HIDE 16

#define KOOPA_HIDE_TIMEOUT 10000
#define KOOPA_WAKE_UP_TIMEOUT 500

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_HIDE 200
#define KOOPA_STATE_WAKE_UP 300
#define KOOPA_STATE_KICKED 400
#define KOOPA_STATE_PICKED_UP 500

#define ID_ANI_KOOPA_WALKING "koopa_walk"
#define ID_ANI_KOOPA_HIDE "koopa_hide"
#define ID_ANI_KOOPA_WAKE_UP "koopa_wake_up"


class Koopa : public GameObject
{
protected:
	float ax;
	float ay;

	int nx;

	ULONGLONG hide_start;
	ULONGLONG wakeup_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking(float nx, float ny) { return 0 ; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);


public:
	Koopa(float x, float y);
	virtual void SetState(int state);
	void SetDirection(int nx) { this->nx = nx; }
};