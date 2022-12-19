#pragma once
#include "GameObject.h"

#define TAIL_WIDTH 10
#define TAIL_HEIGHT 4
#define TAIL_WHOOP_SPEED 0.1f

class Tail :
    public GameObject
{
public:
	Tail(float x, float y) : GameObject(x, y) {vy = 0.1f; vx = TAIL_WHOOP_SPEED; };
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() {
		return 1;
	};
	virtual int IsBlocking(float nx, float ny) { return 0; }
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

