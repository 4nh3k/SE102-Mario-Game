#pragma once
#include "Goomba.h"

#define ID_ANI_PARA_GOOMBA_WALKING "paragoomba_walk"
#define ID_ANI_PARA_GOOMBA_DIE "paragoomba_die"
#define ID_ANI_PARA_GOOMBA_DIE_UPSIDE_DOWN "paragoomba_die_up_side_down"
#define ID_ANI_PARA_GOOMBA_WING_CLOSE "paragoomba_wing_close"
#define ID_ANI_PARA_GOOMBA_FLY "paragoomba_fly"

#define PARA_GOOMBA_FLY_SPEED_Y 0.25f
#define PARA_GOOMBA_SMALL_JUMP_SPEED_Y 0.08f
#define PARA_GOOMBA_SMALL_JUMP_LIMIT 3
#define PARA_GOOMBA_WALK_TIMEOUT 2000

class ParaGoomba : public Goomba
{
protected:
	ULONGLONG timer;
	bool hasWing;
	bool isFlying;
	int jumpCount;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) ;
	virtual void Render();
public:
	ParaGoomba(float x, float y) : Goomba(x, y) { hasWing = true; jumpCount = 0; isFlying = false; };
	bool HasWing() { return hasWing; }
	void SetWing(bool hasWing) { this->hasWing = hasWing; }
};

