#include "ParaKoopa.h"
void ParaKoopa::Render()
{
	if (!HasWing() || state == KOOPA_STATE_DIE)
	{
		Koopa::Render();
		return;
	}
	string aniId = ID_ANI_PARA_KOOPA_FLY_LEFT;
	if (vx > 0)
	{
		aniId = ID_ANI_PARA_KOOPA_FLY_RIGHT;
	}
	Animations::GetInstance()->Get(aniId)->Render(x, y);

}
void ParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (isOnPlatform && HasWing())
	{
		vy = -PARA_KOOPA_FLY_SPEED_Y;
	}
	isOnPlatform = false;
	Collision::GetInstance()->Process(this, dt, coObjects);
}