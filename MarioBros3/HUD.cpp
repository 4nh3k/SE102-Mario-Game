#include "HUD.h"
void HUD::Render()
{
	Animations::GetInstance()->Get(ANI_ID_HUD)->Render(x, y);
	life->Render();
	coin->Render();
	score->Render();
	timer->Render();
}