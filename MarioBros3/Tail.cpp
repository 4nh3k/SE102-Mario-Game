#include "Tail.h"
void Tail::Render()
{
	RenderBoundingBox();
}

void Tail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking(e->nx, e->ny)) return;
	DebugOutTitle(L"nx: %f, ny: %f", e->nx, e->ny);
	if (e->ny != 0)
	{
		//vy = 0;
	}
	else
	{
	}
}
void Tail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TAIL_WIDTH / 2;
	t = y - TAIL_HEIGHT / 2;
	r = l + TAIL_WIDTH;
	b = t + TAIL_HEIGHT;
}