#pragma once
#include "GameObject.h"

#define ID_ANI_VANISH   "vanish_sfx"
#define ID_ANI_HIT      "hit_sfx"
class SFX :
    public GameObject
{
	ULONGLONG timer;
	string aniId;
public:
	SFX(float x, float y, string aniId) : GameObject(x, y) { timer = GetTickCount64(); this->aniId = aniId; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking(float nx, float ny) { return 0; }
};

