#pragma once
#include "GameObject.h"

#define ID_ANI_VANISH   "vanish_sfx"
#define ID_ANI_HIT      "hit_sfx"
class SFX :
    public GameObject
{
protected:
	ULONGLONG timer;
	string aniId;
public:
	SFX(float x, float y, string aniId) : GameObject(x, y) { timer = GetTickCount64(); this->aniId = aniId; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

