#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.03f
#define GOOBA_DIE_SPEED_Y 0.25f
#define GOOBA_DIE_SPEED_X 0.1f

#define GOOMBA_BBOX_WIDTH 16u
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_DIE_UP_SIDE_DOWN 201

#define ID_ANI_GOOMBA_WALKING "goomba_walk"
#define ID_ANI_GOOMBA_DIE "goomba_die"
#define ID_ANI_GOOMBA_DIE_UP_SIDE_DOWN "goomba_die_up_side_down"

class Goomba : public GameObject
{
protected:
	float ax;				
	float ay; 

	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != GOOMBA_STATE_DIE_UP_SIDE_DOWN); };
	virtual int IsBlocking(float nx, float ny) { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	float nx;
	Goomba(float x, float y);
	virtual void SetState(int state);
};