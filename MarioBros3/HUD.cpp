#include "HUD.h"

HUD* HUD::__instance = NULL;
void HUD::Render()
{
	Animations::GetInstance()->Get(ANI_ID_HUD)->Render(x, y);
	life->Render();
	coin->Render();
	score->Render();
	timer->Render();
	momentumBar->Render();
}
HUD* HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD(0,0);
	return HUD::__instance;
}
void HUD::SetPosition(float x, float y) {
	this->x = x, this->y = y;
	coin->SetPos(x + COIN_POS_OFFSET_X, y + COIN_POS_OFFSET_Y);
	life->SetPos(x + LIFE_POS_OFFSET_X, y + LIFE_POS_OFFSET_Y);
	score->SetPos(x + SCORE_POS_OFFSET_X, y + SCORE_POS_OFFSET_Y);
	timer->SetPos(x + TIMER_POS_OFFSET_X, y + TIMER_POS_OFFSET_Y);
	momentumBar->SetPos(x + MOMENTUMBAR_POS_OFFSET_X, y + MOMENTUMBAR_POS_OFFSET_Y);
}
void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Mario* player = dynamic_cast<Mario*>(Game::GetInstance()->GetCurrentScene()->GetPlayer());
	life->SetNumber(2);
	coin->SetNumber(player->GetCoin());
	score->SetNumber(player->GetScore());
	int timerNum = PLAYSCENE_TIME - (GetTickCount64() - time) / 1000;
	timer->SetNumber(timerNum);
	//momentumBar->SetNode(1);
} 