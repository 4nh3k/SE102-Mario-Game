#include "GhostBlock.h"
#include "Platform.h"
#include "SpecialPlatform.h"

void GhostBlock::Render()
{
	RenderBoundingBox();
}

void GhostBlock::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking(e->nx, e->ny)) return;
	if (e->ny != 0)
	{
		onPlatform = true;
		//vy = 0;
	}
	else
	{
	}
}

void GhostBlock::OnNoCollision(DWORD dt)
{
	onPlatform = false;
	DebugOutTitle(L"no collision");
}

void GhostBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOutTitle(L"vx: %f, vy: %f", vx, vy);
	Collision::GetInstance()->Process(this, dt, coObjects);
}

void GhostBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 10 / 2;
	t = y - KOOPA_BBOX_HEIGHT / 2;
	r = l + 10;
	b = t + KOOPA_BBOX_HEIGHT;
}