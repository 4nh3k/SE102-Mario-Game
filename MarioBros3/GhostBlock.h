#pragma once
#include "GameObject.h"
#include "Koopa.h"

class GhostBlock :
    public GameObject
{
	bool onPlatform;
public:
	GhostBlock(float x, float y) : GameObject(x, y) { onPlatform = false; vy = 0.1f; vx = KOOPA_WALKING_SPEED;  };
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() {	
		return 1;
	};
	int IsOnPlatform() { return onPlatform;  }
	virtual int IsBlocking(float nx, float ny) { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

