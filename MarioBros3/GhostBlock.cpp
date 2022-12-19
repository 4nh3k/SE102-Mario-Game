#include "GhostBlock.h"

void GhostBlock::Render()
{
	RenderBoundingBox();
}

void GhostBlock::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking(e->nx, e->ny)) return;
	DebugOutTitle(L"nx: %f, ny: %f", e->nx, e->ny);
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
	vx = -vx;
	onPlatform = false;
}

void GhostBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Collision::GetInstance()->Process(this, dt, coObjects);
}

void GhostBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GHOSTBLOCK_WIDTH / 2;
	t = y - KOOPA_BBOX_HEIGHT / 2;
	r = l + GHOSTBLOCK_WIDTH;
	b = t + KOOPA_BBOX_HEIGHT;
}