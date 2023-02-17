#pragma once
#include "GameObject.h"

#define ANI_ID_TURTLE_WALK_LEFT "turtle_walk_left"
#define ANI_ID_TURTLE_WALK_RIGHT "turtle_walk_right"

#define TURTLE_WALK_DISTANCE 16
#define TURTLE_WALK_SPEED 0.02f

class MapTurtle :
    public GameObject
{
	float oldX;
public:
	MapTurtle(float x, float y) : GameObject(x, y) 
	{
		oldX = x;
		vx = TURTLE_WALK_SPEED;
	}
	void Render()
	{
		if (vx > 0)
		{
			Animations::GetInstance()->Get(ANI_ID_TURTLE_WALK_RIGHT)->Render(x, y);
		}
		else
		{
			Animations::GetInstance()->Get(ANI_ID_TURTLE_WALK_LEFT)->Render(x, y);
		}
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		x += vx * dt;
		if (abs(oldX - x) > TURTLE_WALK_DISTANCE)
		{
			oldX = x;
			vx = -vx;
		}
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

