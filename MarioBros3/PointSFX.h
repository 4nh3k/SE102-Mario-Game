#pragma once
#include "SFX.h"
#define DELETE_TIME 500
#define RISE_UP_SPEED 0.05f

#define ID_ANI_100POINT "100point"
#define ID_ANI_200POINT "200point"
#define ID_ANI_400POINT "400point"
#define ID_ANI_800POINT "800point"
#define ID_ANI_1000POINT "1000point"
#define ID_ANI_2000POINT "2000point"
#define ID_ANI_4000POINT "4000point"
#define ID_ANI_8000POINT "8000point"
#define ID_ANI_1UP		"1up"

class PointSFX : public SFX
{
public:
	PointSFX(float x, float y, string aniId) : SFX(x, y, aniId) { vy = -RISE_UP_SPEED; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	static string GetAniId(int point);
};

