#pragma once
#include "GameObject.h"
#include "MomentumBar.h"
#include "Font.h"
#include "Mario.h"
#include "Card.h"

#define HUD_WIDTH 250
#define HUD_HEIGHT 36

#define CARD_COUNT 3

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
#define CARD_POS_OFFSET_Y 1
#define CARD_POS_OFFSET_X 52

#define MARIO_INIT_LIFE 4 

#define PLAYSCENE_TIME 300

#define ANI_ID_HUD "HUD"

class HUD : public GameObject
{
	int currentTime;
	bool finishScene;
	static HUD* __instance;
	int life;
	int coin;
	int score;
	int cardCount;
	DWORD time;
	Font* FLife;
	Font* FCoin;
	Font* FScore;
	Font* FTimer;
	MomentumBar* momentumBar;
	vector<Card*> cards;
	bool stopTimer;
	bool isGameOver;
	bool hasFinish; 
public:
	HUD(float x, float y) : GameObject(x,y)
	{
		currentTime = PLAYSCENE_TIME;
		life = MARIO_INIT_LIFE;
		coin = 0;
		score = 0;
		FTimer = new Font(x, y, 3);
		FCoin = new Font(x, y, 2);
		FLife = new Font(x, y, 2);
		FScore = new Font(x, y, 7);
		Card* tmp = new Card(x, y, -1);
		cards.push_back(tmp);
		tmp = new Card(x, y, -1);
		cards.push_back(tmp);
		tmp = new Card(x, y, -1);
		FCoin->SetNumber(coin);
		FLife->SetNumber(life);
		FScore->SetNumber(score);
		cards.push_back(tmp);
		finishScene = false;
		hasFinish = false;
		momentumBar = MomentumBar::GetInstance();
		cardCount = 0;
		ResetTimer();
	}
	static HUD* GetInstance();
	void SetPosition(float x, float y);
	void Render();
	void StopTimer();
	void StartTimer();
	void ResetTimer();
	void FinishScene();
	void AddScore(int point);
	void AddCoin();
	void AddCard(int type);
	void AddLife(int life);
	void DecreseLife();
	bool HasFinishScene()
	{
		return hasFinish;
	}
	void SetHasFinishScene(bool hasFinish = false)
	{
		this->hasFinish = hasFinish;
	}
	static void Delete()
	{
		__instance->isDeleted = true;
		__instance = NULL;
	}
	bool IsGameOver() {
		return isGameOver;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

