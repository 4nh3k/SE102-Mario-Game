#pragma once
#include "GameObject.h"
#include "Font.h"
#include "Mario.h"
#define HUD_WIDTH 250
#define HUD_HEIGHT 36
#define COIN_POS_OFFSET_X (141 - HUD_WIDTH /2)
#define COIN_POS_OFFSET_Y (14 - HUD_HEIGHT /2)
#define SCORE_POS_OFFSET_X (61 - HUD_WIDTH /2)
#define SCORE_POS_OFFSET_Y (22 - HUD_HEIGHT /2)
#define LIFE_POS_OFFSET_X (38 - HUD_WIDTH /2)
#define LIFE_POS_OFFSET_Y (22 - HUD_HEIGHT /2)
#define TIMER_POS_OFFSET_X (133 - HUD_WIDTH /2)
#define TIMER_POS_OFFSET_Y (22 - HUD_HEIGHT /2)
#define PLAYSCENE_TIME 300

#define ANI_ID_HUD "HUD"

class HUD : public GameObject
{
	DWORD time;
	Font* life;
	Font* coin;
	Font* score;
	Font* timer;
public:
	HUD(float x, float y) : GameObject(x,y)
	{
		timer = new Font(x, y, 3);
		coin = new Font(x, y, 2);
		life = new Font(x, y, 2);
		score = new Font(x, y, 7);
		time = GetTickCount64();
	}
	void SetPosition(float x, float y) {
		this->x = x, this->y = y; 
		coin->SetPos(x + COIN_POS_OFFSET_X, y + COIN_POS_OFFSET_Y);
		life->SetPos(x + LIFE_POS_OFFSET_X, y + LIFE_POS_OFFSET_Y);
		score->SetPos(x + SCORE_POS_OFFSET_X, y + SCORE_POS_OFFSET_Y);
		timer->SetPos(x + TIMER_POS_OFFSET_X, y + TIMER_POS_OFFSET_Y);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		Mario* player = dynamic_cast<Mario*>(Game::GetInstance()->GetCurrentScene()->GetPlayer());
		life->SetNumber(2);
		coin->SetNumber(player->GetCoin());
		score->SetNumber(player->GetScore());
		int timerNum = PLAYSCENE_TIME - (GetTickCount64() - time) / 1000;
		timer->SetNumber(timerNum);
	};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

