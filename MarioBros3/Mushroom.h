#pragma once
#include "GameObject.h" 
#define REWARD_COIN_ANI_ID "coin_rotate"
#define MUSHROOM_WIDTH 16
#define MUSHROOM_HEIGHT 16
#define MUSHROOM_GRAVITY 0.002f
class Mushroom : public GameObject
{
	bool startMoving = false;
	float oldY;
	float ay;
public:
	Mushroom(float x, float y) : GameObject(x, y) {
		this->ay = MUSHROOM_GRAVITY;

		oldY =y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() {
		return (startMoving == true);
	};
	virtual int IsBlocking(float nx, float ny) { return 0; }
	void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

