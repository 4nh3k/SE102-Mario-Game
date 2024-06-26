#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK "brick"
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class Brick : public GameObject {
public:
	Brick(float x, float y) : GameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void Break();
	void Accept(CollisionVisitor* visitor) {
		visitor->VisitBrick();
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};