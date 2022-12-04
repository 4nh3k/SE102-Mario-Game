#include "Mushroom.h"

void Mushroom::Render()
{
	Animations* animations = Animations::GetInstance();
	switch (state)
	{
		animations->Get(REWARD_COIN_ANI_ID)->Render(x, y);
	}
	animations->Get(REWARD_COIN_ANI_ID)->Render(x, y);

	//RenderBoundingBox();
}

void Mushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking(e->nx, e->ny)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}
void Mushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (startMoving)
	{
		vy += ay * dt;
		Collision::GetInstance()->Process(this, dt, coObjects);
	}
	else
	{
		y += vy * dt;
	}
	if (y < oldY - MUSHROOM_HEIGHT)
	{
		//this->ay = MUSHROOM_GRAVITY;

		startMoving = true;
		vy = 0;
	}
	else
	{
	}
}
void Mushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Mushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_WIDTH / 2;
	t = y - MUSHROOM_HEIGHT / 2;
	r = l + MUSHROOM_WIDTH;
	b = t + MUSHROOM_HEIGHT;
}