#include "RedKoopa.h"

void RedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Koopa::Update(dt, coObjects);
	if (state == KOOPA_STATE_WALKING && !dynamic_cast<GhostBlock*>(ghostBlock)->IsOnPlatform())
	{
		vx = -vx;
	}
	if(state == KOOPA_STATE_WALKING && vx > 0)
		ghostBlock->SetPosition(x  + GHOSTBLOCK_WIDTH/2, y);
	else
	{
		ghostBlock->SetPosition(x  - GHOSTBLOCK_WIDTH/2 , y);
	}
}
string RedKoopa::GetAniId()
{
	string aniId = ID_ANI_RED_KOOPA_WALK_RIGHT;
	if (state == KOOPA_STATE_WALKING)
	{
		if (vx < 0)
			aniId = ID_ANI_RED_KOOPA_WALK_LEFT;
		else
			aniId = ID_ANI_RED_KOOPA_WALK_RIGHT;
	}
	else if (state == KOOPA_STATE_HIDE || state == KOOPA_STATE_PICKED_UP)
		aniId = ID_ANI_RED_KOOPA_HIDE;
	else if (state == KOOPA_STATE_KICKED)
		aniId = ID_ANI_RED_KOOPA_KICKED;
	else if (state == KOOPA_STATE_WAKE_UP)
		aniId = ID_ANI_RED_KOOPA_WAKE_UP;
	else if (state == KOOPA_STATE_DIE)
		aniId = ID_ANI_RED_KOOPA_HIDE_UPSIDE_DOWN;
	return aniId;
}
string RedKoopa::GetAniIdUpsideDown()
{
	string aniId = ID_ANI_RED_KOOPA_HIDE_UPSIDE_DOWN;
	if (state == KOOPA_STATE_HIDE || state == KOOPA_STATE_PICKED_UP)
		aniId = ID_ANI_RED_KOOPA_HIDE_UPSIDE_DOWN;
	else if (state == KOOPA_STATE_KICKED)
		aniId = ID_ANI_RED_KOOPA_KICKED_UPSIDE_DOWN;
	else if (state == KOOPA_STATE_WAKE_UP)
		aniId = ID_ANI_RED_KOOPA_WAKE_UP_UPSIDE_DOWN;
	return aniId;
}
