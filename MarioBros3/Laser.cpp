#include "Laser.h"
void Laser::Render()
{
	Animations::GetInstance()->Get(ID_ANI_LASER)->Render(x,y);
	//RenderBoundingBox();
}

void Laser::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking(e->nx, e->ny)) return;
	DebugOutTitle(L"nx: %f, ny: %f", e->nx, e->ny);
}


void Laser::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 4 / 2;
	t = y - 4 / 2;
	r = l + 4;
	b = t + 4;
}
void Laser::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	Collision::GetInstance()->Process(this, dt, coObjects);

}