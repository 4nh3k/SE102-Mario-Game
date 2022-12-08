#include "Koopa.h"
#include "Goomba.h"

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
	if (state == KOOPA_STATE_WALKING)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_HIDE / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_HIDE;
		
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

	if (e->ny != 0)
	{ 
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	
	if (state == KOOPA_STATE_KICKED)
	{
		if (dynamic_cast<Koopa*>(e->obj)) OnCollisionWithKoopa(e);
		else if (dynamic_cast<Goomba*>(e->obj)) OnCollisionWithGoomba(e);
		DebugOutTitle(L"nx: %f, ny: %f", e->nx, e->ny);
	}
}

void Koopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	Goomba* goomba = dynamic_cast<Goomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
	}
}
void Koopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{

}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_HIDE) && (GetTickCount64() - hide_start > KOOPA_HIDE_TIMEOUT))
	{
		SetState(KOOPA_STATE_WAKE_UP);
	}
	if ((state == KOOPA_STATE_WAKE_UP) && (GetTickCount64() - wakeup_start > KOOPA_WAKE_UP_TIMEOUT))
	{
		// push koopa up a bit so it not stuck under ground
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_HIDE)/2;
		SetState(KOOPA_STATE_WALKING);
	}
	//DebugOutTitle(L" x: %f, y: %f", x, y);

	GameObject::Update(dt, coObjects);
	Collision::GetInstance()->Process(this, dt, coObjects);
}


void Koopa::Render()
{
	string aniId = ID_ANI_KOOPA_WALKING;
	if (state == KOOPA_STATE_HIDE || state == KOOPA_STATE_KICKED || state == KOOPA_STATE_PICKED_UP)
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
		//y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_HIDE) / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED ;
		break;
	case KOOPA_STATE_WAKE_UP:
		wakeup_start = GetTickCount64();
		break;
	case KOOPA_STATE_KICKED:
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_PICKED_UP:
		y -= 10;
		ay = 0;
	}
}
