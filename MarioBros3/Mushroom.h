#pragma once
#include "GameObject.h" 
#define ID_ANI_LEVEL_UP_MUSHROOM "level_up_mushroom"
#define MUSHROOM_WIDTH 16
#define MUSHROOM_HEIGHT 16
#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_RAISE_UP_SPEED -0.02f
#define MUSHROOM_SPEED 0.06f

class Mushroom : public GameObject
{
	bool startMoving;
	float oldY;
	float ay;
public:
	Mushroom(float x, float y) : GameObject(x, y) {
		startMoving = false;
		vy = MUSHROOM_RAISE_UP_SPEED;
		this->ay = MUSHROOM_GRAVITY;
		oldY =y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() {
		return 1;
	};
	virtual int IsBlocking(float nx, float ny) { return 0; }
	void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void Accept(CollisionVisitor* visitor) {
		visitor->VisitMushroom();
	}
};

