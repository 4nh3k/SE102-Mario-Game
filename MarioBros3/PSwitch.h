#pragma once
#include "GameObject.h"
#include "SFX.h"

#define PSWITCH_STATE_IDLE 0
#define PSWITCH_STATE_HIT 1
#define ID_ANI_PSWITCH_IDLE "P_switch_idle"
#define ID_ANI_PSWITCH_HIT "P_switch_hit"
#define PSWITCH_BBOX_WIDTH 16
#define PSWITCH_IDLE_BBOX_HEIGHT 16
#define PSWITCH_HIT_BBOX_HEIGHT 6

class PSwitch : public GameObject
{
	LPGAMEOBJECT sfx;
	bool startRender;
public:
	PSwitch(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() {	return 1;}
	virtual int IsBlocking(float nx, float ny) { return (state == PSWITCH_STATE_IDLE);}
	void TurnBrickIntoCoin();
	void SetState(int state);
};

