#include "Koopa.h"

Koopa::Koopa(float x, float y) :GameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	hide_start = -1;
	wakeup_start = -1 ;
	SetState(KOOPA_STATE_WALKING);
}

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_HIDE)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_HIDE / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_HIDE;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking(e->nx, e->ny)) return;
	if (dynamic_cast<Koopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_HIDE) && (GetTickCount64() - hide_start > KOOPA_HIDE_TIMEOUT))
	{
		state = KOOPA_STATE_WAKE_UP;
		wakeup_start = GetTickCount64();
	}
	if ((state == KOOPA_STATE_WAKE_UP) && (GetTickCount64() - wakeup_start > KOOPA_WAKE_UP_TIMEOUT))
	{
		// push koopa up a bit so it not stuck under ground
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_HIDE);
		state = KOOPA_STATE_WALKING;
		vx = -KOOPA_WALKING_SPEED;
	}

	GameObject::Update(dt, coObjects);
	Collision::GetInstance()->Process(this, dt, coObjects);
}


void Koopa::Render()
{
	string aniId = ID_ANI_KOOPA_WALKING;
	if (state == KOOPA_STATE_HIDE)
	{
		aniId = ID_ANI_KOOPA_HIDE;
	}
	else if (state == KOOPA_STATE_WAKE_UP)
	{
		aniId = ID_ANI_KOOPA_WAKE_UP;
	}

	Animations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void Koopa::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_HIDE:
		hide_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_HIDE) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	}
}
