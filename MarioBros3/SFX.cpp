#include "SFX.h"
void SFX::Render()
{
	Animations::GetInstance()->Get(aniId)->Render(x, y, false);
}
void SFX::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - timer >= Animations::GetInstance()->Get(aniId)->GetAniTime())
	{
		this->Delete();
	}
}