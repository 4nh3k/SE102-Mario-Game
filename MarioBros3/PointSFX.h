#pragma once
#include "SFX.h"
#define DELETE_TIME 500
#define POINT_RISE_UP_SPEED 0.05f
#define LIFE_RISE_UP_SPEED 0.1f

#define ID_ANI_100POINT		"100point"
#define ID_ANI_200POINT		"200point"
#define ID_ANI_400POINT		"400point"
#define ID_ANI_800POINT		"800point"
#define ID_ANI_1000POINT	"1000point"
#define ID_ANI_2000POINT	"2000point"
#define ID_ANI_4000POINT	"4000point"
#define ID_ANI_8000POINT	"8000point"
#define ID_ANI_1UP			"1up"
#define ID_ANI_GOAL_1UP		"goal_1up"
#define ID_ANI_GOAL_2UP		"goal_2up"
#define ID_ANI_GOAL_3UP		"goal_3up"
#define ID_ANI_GOAL_5UP		"goal_5up"


class PointSFX : public SFX
{
	int timeout;
public:
	PointSFX(float x, float y, string aniId, bool isGoal = false) : SFX(x, y, aniId) 
	{
		if (!isGoal)
		{
			vy = -POINT_RISE_UP_SPEED;
			timeout = DELETE_TIME;
		}
		else
		{
			vy = -LIFE_RISE_UP_SPEED;
			timeout = DELETE_TIME * 3;
		}
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	static string GetAniId(int point);
};

