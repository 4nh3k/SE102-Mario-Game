#pragma once
#include "GameObject.h"

#define ID_ANI_LASER "laser"
#define LASER_SPEED 0.02f

class Laser :
    public GameObject
{
public:
	Laser(float x, float y) : GameObject(x, y) { vy = 0.02f; vx = 0.02f;};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() {
		return 1;
	}
	virtual int IsGoThrough() { return 1; }
	virtual int IsBlocking(float nx, float ny) { return 0; }
	void Accept(CollisionVisitor* visitor) {
		visitor->VisitLaser();
	}
};

