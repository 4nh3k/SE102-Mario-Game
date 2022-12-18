#pragma once
#include "GameObject.h"

#define ID_ANI_SUPER_LEAF_LEFT "super_leaf_left"
#define ID_ANI_SUPER_LEAF_RIGHT "super_leaf_right"

#define SUPER_LEAF_BBOX_WIDTH 14
#define SUPER_LEAF_BBOX_HEIGHT 16
#define SUPER_LEAF_RISE_UP_SPEED -0.1f
#define SUPER_LEAF_FALL_DOWN_WIDTH 20
#define SUPER_LEAF_RISE_UP_HEIGHT 48
#define SUPER_LEAF_FALL_DOWN_SPEED 0.02f
#define SUPER_LEAF_FALL_DOWN_SIDE_SPEED 0.05f


class SuperLeaf : public GameObject
{
	float oldY;
	float oldX;
public:
	SuperLeaf(float x, float y) : GameObject(x, y) {
		vy = SUPER_LEAF_RISE_UP_SPEED;
		oldY = y;
		oldX = x;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking(float nx, float ny) { return 0; }
	int IsGoThrough() { return 1; }
	virtual int IsCollidable() {
		return 1;
	};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

