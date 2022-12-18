#include "RedKoopa.h"

void RedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Koopa::Update(dt, coObjects);
	if (state == KOOPA_STATE_WALKING && !dynamic_cast<GhostBlock*>(ghostBlock)->IsOnPlatform())
	{
		vx = -vx;
	}
	if(state == KOOPA_STATE_WALKING && vx > 0)
		ghostBlock->SetPosition(x + KOOPA_BBOX_WIDTH / 2 + 5, y);
	else
	{
		ghostBlock->SetPosition(x - KOOPA_BBOX_WIDTH / 2 - 5, y);
	}
}