#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.0008f
#define KOOPA_WALKING_SPEED 0.03f
#define KOOPA_KICKED_SPEED 0.18f

#define KOOPA_TAIL_WHOOP_SPEED_Y 0.25f
#define KOOPA_DIE_Y 0.25f
#define KOOPA_TAIL_WHOOP_SPEED_X 0.1f

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_HIDE 14
#define KOOPA_HIDE_TIMEOUT 10000
#define KOOPA_WAKE_UP_TIMEOUT 500

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_HIDE 200
#define KOOPA_STATE_WAKE_UP 300
#define KOOPA_STATE_KICKED 400
#define KOOPA_STATE_PICKED_UP 500
#define KOOPA_STATE_UPSIDE_DOWN 600 
#define KOOPA_STATE_DIE 700 

#define ID_ANI_KOOPA_WALK_RIGHT "koopa_walk_right"
#define ID_ANI_KOOPA_WALK_LEFT "koopa_walk_left"
#define ID_ANI_KOOPA_KICKED "koopa_kicked"
#define ID_ANI_KOOPA_HIDE "koopa_hide"
#define ID_ANI_KOOPA_WAKE_UP "koopa_wake_up"

#define ID_ANI_KOOPA_KICKED_UPSIDE_DOWN "koopa_kicked_up_side_down"
#define ID_ANI_KOOPA_HIDE_UPSIDE_DOWN "koopa_hide_up_side_down"
#define ID_ANI_KOOPA_WAKE_UP_UPSIDE_DOWN "koopa_wake_up_up_side_down"



class Koopa : public GameObject
{
protected:
	float ax;
	float ay;

	int combo;
	int nx;

	LPGAMEOBJECT sfx;

	bool isOnPlatform;
	bool isUpsideDown;

	ULONGLONG hide_start;
	ULONGLONG wakeup_start;	
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != KOOPA_STATE_DIE); };
	virtual int IsBlocking(float nx, float ny) { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void AddScore();

public:
	Koopa(float x, float y);
	virtual void SetState(int state);
	virtual string GetAniId();
	virtual string GetAniIdUpsideDown();
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	bool IsUpsideDown() { return isUpsideDown; }
	void SetDirection(int nx) { this->nx = nx; }
	void Accept(CollisionVisitor* visitor) {
		visitor->VisitKoopa();
	}
};