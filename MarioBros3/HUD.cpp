#include "HUD.h"
#include "MarioMap.h"
#include "PointSFX.h"

HUD* HUD::__instance = NULL;
void HUD::Render()
{
	Animations::GetInstance()->Get(ANI_ID_HUD)->Render(x, y);
	FLife->Render();
	FCoin->Render();
	FScore->Render();
	FTimer->Render();
	momentumBar->Render();
	for (auto i : cards)
	{
		i->Render();
	}
}
HUD* HUD::GetInstance()
{
	if (__instance == NULL) 
		__instance = new HUD(0,0);
	return HUD::__instance;
}
void HUD::SetPosition(float x, float y) {
	this->x = x, this->y = y;
	FCoin->SetPosition(x + COIN_POS_OFFSET_X, y + COIN_POS_OFFSET_Y);
	FLife->SetPosition(x + LIFE_POS_OFFSET_X, y + LIFE_POS_OFFSET_Y);
	FScore->SetPosition(x + SCORE_POS_OFFSET_X, y + SCORE_POS_OFFSET_Y);
	FTimer->SetPosition(x + TIMER_POS_OFFSET_X, y + TIMER_POS_OFFSET_Y);
	momentumBar->SetPos(x + MOMENTUMBAR_POS_OFFSET_X, y + MOMENTUMBAR_POS_OFFSET_Y);
 	for (int i = 0; i < CARD_COUNT; i++)
	{
		cards[i]->SetPosition(x + CARD_POS_OFFSET_X + 24 * i, y - CARD_POS_OFFSET_Y);
	}
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
	if (finishScene)
	{
		if (currentTime < 3)
		{
			AddScore(currentTime * 50);
			currentTime = 0;
		}
		else
		{
			AddScore(150);
			currentTime-=3;
		}
		if (currentTime <= 0)
		{
			finishScene = false;
			hasFinish = true;
		}
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
	FCoin->SetNumber(coin);

}
void HUD::AddLife(int life)
{
	this->life += life;
	FLife->SetNumber(this->life);
}
void HUD::DecreseLife()
{
	if (life == 0)
	{
		isGameOver = true;
		return;
	}
	life--;
	FLife->SetNumber(life);
}
void HUD::AddScore(int point)
{
	score += point;
	FScore->SetNumber(score);
}
void HUD::AddCard(int type)
{
	cards[cardCount]->SetCardType(type);
	cardCount++;
	if (cardCount >= CARD_COUNT)
	{
		string aniId = ID_ANI_GOAL_1UP;
		if (cards[0]->GetCardType() != cards[1]->GetCardType() || cards[0]->GetCardType() != cards[2]->GetCardType() || cards[1]->GetCardType() != cards[2]->GetCardType())
		{
			AddLife(1);
		}
		if (cards[0]->GetCardType() == cards[1]->GetCardType() && cards[1]->GetCardType() == cards[2]->GetCardType())
		{
			switch (cards[0]->GetCardType())
			{
			case CARD_MUSHROOM_ID:
				aniId = ID_ANI_GOAL_2UP;
				AddLife(2);
				break;
			case CARD_FLOWER_ID:
				aniId = ID_ANI_GOAL_3UP;
				AddLife(3);
				break;
			case CARD_STAR_ID:
				aniId = ID_ANI_GOAL_5UP;
				AddLife(5);
				break;
			default:
				break;
			}
		}
		Game::GetInstance()->GetCurrentScene()->AddSFX(new PointSFX(x, y, aniId, true));
		for (int i = 0; i < CARD_COUNT; i++)
		{
			cards[i]->SetCardType(-1);
		}
		cardCount = 0;
	}
}
void HUD::FinishScene()
{
	StopTimer();
	finishScene = true;
}