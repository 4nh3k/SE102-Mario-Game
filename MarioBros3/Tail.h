#pragma once
#include "GameObject.h"
#include "MarioConst.h"
#define TAIL_WIDTH 10
#define TAIL_HEIGHT 4
#define TAIL_WHACK_SPEED 0.0f
#define TAIL_CHANGE_SIDE_TIME MARIO_TAIL_WHACK_TIMEOUT/2

class Tail :
    public GameObject
{
	float hasChangedSide = false;
	float timer;
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
public:
	Tail(float x, float y) : GameObject(x, y) { vy = 0.0f; vx = TAIL_WHACK_SPEED; timer = GetTickCount64(); };
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() {
		return 1;
	};
	virtual int IsBlocking(float nx, float ny) { return 1; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

