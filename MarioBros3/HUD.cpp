#include "HUD.h"

HUD* HUD::__instance = NULL;
void HUD::Render()
{
	Animations::GetInstance()->Get(ANI_ID_HUD)->Render(x, y);
	FLife->Render();
	FCoin->Render();
	FScore->Render();
	FTimer->Render();
	momentumBar->Render();
}
HUD* HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD(0,0);
	return HUD::__instance;
}
void HUD::SetPosition(float x, float y) {
	this->x = x, this->y = y;
	FCoin->SetPos(x + COIN_POS_OFFSET_X, y + COIN_POS_OFFSET_Y);
	FLife->SetPos(x + LIFE_POS_OFFSET_X, y + LIFE_POS_OFFSET_Y);
	FScore->SetPos(x + SCORE_POS_OFFSET_X, y + SCORE_POS_OFFSET_Y);
	FTimer->SetPos(x + TIMER_POS_OFFSET_X, y + TIMER_POS_OFFSET_Y);
	momentumBar->SetPos(x + MOMENTUMBAR_POS_OFFSET_X, y + MOMENTUMBAR_POS_OFFSET_Y);
}
void HUD::StartTimer()
{
	time = GetTickCount64() - (PLAYSCENE_TIME - currentTime)*1000;
	stopTimer = false;
}
void HUD::StopTimer()
{
	stopTimer = true;
}
void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Mario* player = dynamic_cast<Mario*>(Game::GetInstance()->GetCurrentScene()->GetPlayer());
	FLife->SetNumber(2);
	FCoin->SetNumber(coin);
	FScore->SetNumber(score);
	if (!stopTimer)
	{
		int timerNum = PLAYSCENE_TIME - (GetTickCount64() - time) / 1000;
		FTimer->SetNumber(timerNum);
		currentTime = timerNum;
	}
	else
	{
		FTimer->SetNumber(currentTime);
	}
	//momentumBar->SetNode(1);
} 
void HUD::ResetTimer()
{
	time = GetTickCount64();
	currentTime = PLAYSCENE_TIME;
}
void HUD::AddCoin()
{
	coin++;
}
void HUD::IncreaseLife()
{
	life++;
}
void HUD::DecreseLife()
{
	life--;
}
void HUD::AddScore(int point)
{
	score += point;
}