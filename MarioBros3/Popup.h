#pragma once
#include "GameObject.h"

#define POPUP_TYPE_START 0
#define POPUP_TYPE_GAME_OVER 1

#define DELETE_TIME 2000

#define ID_ANI_POPUP_START "popup_start"
#define ID_ANI_POPUP_GAME_OVER "popup_game_over"


class Popup : public GameObject
{
	int type;
	DWORD timer;
public:
	Popup(float x, float y, int type) : GameObject(x, y)
	{
		this->type = type;
		StartTimer();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (type == POPUP_TYPE_START && GetTickCount64() - timer >= DELETE_TIME)
		{
			this->Delete();
		}
	}
	void Render()
	{
		if(type == POPUP_TYPE_START)
			Animations::GetInstance()->Get(ID_ANI_POPUP_START)->Render(x, y);
		else
		{
			Animations::GetInstance()->Get(ID_ANI_POPUP_GAME_OVER)->Render(x, y);

		}
	}
	void StartTimer()
	{
		timer = GetTickCount64();
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

