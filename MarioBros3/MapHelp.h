#pragma once
#include "SFX.h"

#define HELP_TIMEOUT 1000
class MapHelp :
    public SFX
{
	bool render;
public:
	MapHelp(float x, float y) : SFX(x, y, "help_message") { render = false; }
	void Render()
	{
		if (render)
		{
			Animations::GetInstance()->Get(aniId)->Render(x, y);
		}
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (GetTickCount64() - timer > HELP_TIMEOUT)
		{
			render = !render;
			timer = GetTickCount64();
		}
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

