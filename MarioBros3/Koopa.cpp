#include "Koopa.h"
#include "Goomba.h"
#include "QuestionBlock.h"
#include "VenusFireTrap.h"
Koopa::Koopa(float x, float y) :GameObject(x, y)
{
	isUpsideDown = false;
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	nx = 1;
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
	
	if (state == KOOPA_STATE_KICKED)
	{
		if (dynamic_cast<Koopa*>(e->obj)) OnCollisionWithKoopa(e);
		else if (dynamic_cast<Goomba*>(e->obj)) OnCollisionWithGoomba(e);
		else if (dynamic_cast<QuestionBlock*>(e->obj)) OnCollisionWithQuestionBlock(e);
		else if (dynamic_cast<VenusFireTrap*>(e->obj)) OnCollisionWithVenus(e);
	}

	if (!e->obj->IsBlocking(e->nx, e->ny)) return;

	if (e->ny != 0)
	{ 
		if (isUpsideDown && state == KOOPA_STATE_HIDE)
		{
			vx = 0;
		}
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}
string Koopa::GetAniId()
{
	string aniId = ID_ANI_KOOPA_WALK_RIGHT;
	if (state == KOOPA_STATE_WALKING)
	{
		if (vx < 0)
			aniId = ID_ANI_KOOPA_WALK_LEFT;
		else
			aniId = ID_ANI_KOOPA_WALK_RIGHT;
	}
	else if (state == KOOPA_STATE_HIDE || state == KOOPA_STATE_PICKED_UP)
		aniId = ID_ANI_KOOPA_HIDE;
	else if (state == KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_KICKED;
	else if (state == KOOPA_STATE_WAKE_UP)
		aniId = ID_ANI_KOOPA_WAKE_UP;
	else if (state == KOOPA_STATE_DIE)
		aniId = ID_ANI_KOOPA_HIDE_UPSIDE_DOWN;
	return aniId;
}
string Koopa::GetAniIdUpsideDown()
{
	string aniId = ID_ANI_KOOPA_HIDE_UPSIDE_DOWN;
	if (state == KOOPA_STATE_HIDE || state == KOOPA_STATE_PICKED_UP)
		aniId = ID_ANI_KOOPA_HIDE_UPSIDE_DOWN;
	else if (state == KOOPA_STATE_KICKED)
		aniId = ID_ANI_KOOPA_KICKED_UPSIDE_DOWN;
	else if (state == KOOPA_STATE_WAKE_UP)
		aniId = ID_ANI_KOOPA_WAKE_UP_UPSIDE_DOWN;
	return aniId;
}
void Koopa::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	QuestionBlock* qblock = dynamic_cast<QuestionBlock*>(e->obj);
	if (e->nx != 0)
	{
		if (qblock->GetState() != QUESTION_BLOCK_STATE_HIT)
		{
			qblock->SetState(QUESTION_BLOCK_STATE_HIT);
		}
	}
}

void Koopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	Goomba* goomba = dynamic_cast<Goomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->nx = e->nx;
		goomba->SetState(GOOMBA_STATE_DIE_UPSIDE_DOWN);
	}
}
void Koopa::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	VenusFireTrap* venus = dynamic_cast<VenusFireTrap*>(e->obj);
	if (!venus->IsDeleted())
	{
		venus->Delete();
	}
}
void Koopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
	if (koopa->GetState() != KOOPA_STATE_DIE)
	{
		koopa->SetDirection(e->nx);
		koopa->SetState(KOOPA_STATE_DIE);
	}
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_STATE_DIE))
	{
		isDeleted = true;
		return;
	}

	if ((state == KOOPA_STATE_HIDE || state == KOOPA_STATE_PICKED_UP) && (GetTickCount64() - hide_start > KOOPA_HIDE_TIMEOUT))
	{
		SetState(KOOPA_STATE_WAKE_UP);
	}
	if ((state == KOOPA_STATE_WAKE_UP) && (GetTickCount64() - wakeup_start > KOOPA_WAKE_UP_TIMEOUT))
	{
		isUpsideDown = false;
		// push koopa up a bit so it not stuck under ground
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_HIDE)/2;
		SetState(KOOPA_STATE_WALKING);
	}
	DebugOutTitle(L"x: %f,y: %f,vx: %f,vy: %f,ax: %f,ay: %f", x, y, vx, vy, ax, ay);
	Collision::GetInstance()->Process(this, dt, coObjects);
}


void Koopa::Render()
{
	string aniId;
	if (!isUpsideDown)
		aniId = GetAniId();
	else
		aniId = GetAniIdUpsideDown();
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
		if(!isUpsideDown)
			vx = 0;

		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED ;
		break;
	case KOOPA_STATE_WAKE_UP:
		wakeup_start = GetTickCount64();
		break;
	case KOOPA_STATE_KICKED:
		vx = KOOPA_KICKED_SPEED * nx;
		ay = KOOPA_GRAVITY;
		break;
	case KOOPA_STATE_PICKED_UP:
		wakeup_start = GetTickCount64(); 
		ay = 0;
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_UPSIDE_DOWN:
		vy = -KOOPA_TAIL_WHOOP_SPEED_Y;
		vx = KOOPA_TAIL_WHOOP_SPEED_X * -nx;
		isUpsideDown = true;
		break;
	case KOOPA_STATE_DIE:			
		die_start = GetTickCount64();
		vy = -KOOPA_DIE_Y;
		vx = KOOPA_TAIL_WHOOP_SPEED_X * -nx;
		break;
	}
}
