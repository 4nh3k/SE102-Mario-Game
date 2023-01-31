#pragma once
#include "GameObject.h"
#include "MomentumBar.h"
#include "Font.h"
#include "Mario.h"
#define HUD_WIDTH 250
#define HUD_HEIGHT 36

// first num = real pos on HUD + 4

#define COIN_POS_OFFSET_X (141 - HUD_WIDTH /2)
#define COIN_POS_OFFSET_Y (14 - HUD_HEIGHT /2)
#define SCORE_POS_OFFSET_X (61 - HUD_WIDTH /2)
#define SCORE_POS_OFFSET_Y (22 - HUD_HEIGHT /2)
#define LIFE_POS_OFFSET_X (38 - HUD_WIDTH /2)
#define LIFE_POS_OFFSET_Y (22 - HUD_HEIGHT /2)
#define TIMER_POS_OFFSET_X (133 - HUD_WIDTH /2)
#define TIMER_POS_OFFSET_Y (22 - HUD_HEIGHT /2)
#define MOMENTUMBAR_POS_OFFSET_X (61 - HUD_WIDTH/2)
#define MOMENTUMBAR_POS_OFFSET_Y (14 - HUD_HEIGHT /2)
#define PLAYSCENE_TIME 300

#define ANI_ID_HUD "HUD"

class HUD : public GameObject
{
	int currentTime;
	static HUD* __instance;
	DWORD time;
	Font* life;
	Font* coin;
	Font* score;
	Font* timer;
	MomentumBar* momentumBar;
	bool stopTimer;
public:
	HUD(float x, float y) : GameObject(x,y)
	{
		currentTime = PLAYSCENE_TIME;
		timer = new Font(x, y, 3);
		coin = new Font(x, y, 2);
		life = new Font(x, y, 2);
		score = new Font(x, y, 7);
		momentumBar = MomentumBar::GetInstance();
		time = GetTickCount64();
	}
	static HUD* GetInstance();
	void SetPosition(float x, float y);
	void Render();
	void StopTimer();
	void StartTimer();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

