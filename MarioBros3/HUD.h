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
	int life;
	int coin;
	int score;
	DWORD time;
	Font* FLife;
	Font* FCoin;
	Font* FScore;
	Font* FTimer;
	MomentumBar* momentumBar;
	bool stopTimer;
public:
	HUD(float x, float y) : GameObject(x,y)
	{
		currentTime = PLAYSCENE_TIME;
		life = 3;
		coin = 0;
		score = 0;
		FTimer = new Font(x, y, 3);
		FCoin = new Font(x, y, 2);
		FLife = new Font(x, y, 2);
		FScore = new Font(x, y, 7);
		momentumBar = MomentumBar::GetInstance();
		ResetTimer();
	}
	static HUD* GetInstance();
	void SetPosition(float x, float y);
	void Render();
	void StopTimer();
	void StartTimer();
	void ResetTimer();
	void AddScore(int point);
	void AddCoin();
	void IncreaseLife();
	void DecreseLife();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

