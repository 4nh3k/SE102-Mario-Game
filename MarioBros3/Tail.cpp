#include "Tail.h"
#include "Goomba.h"
#include "QuestionBlock.h"
#include "Koopa.h"
#include "Mario.h"
#include "VenusFireTrap.h"

void Tail::Render()
{
	RenderBoundingBox();
}

void Tail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking(e->nx, e->ny)) return;

	if (dynamic_cast<Goomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<QuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<Koopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<VenusFireTrap*>(e->obj))
		OnCollisionWithVenus(e);
}

void Tail::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	VenusFireTrap* venus = dynamic_cast<VenusFireTrap*>(e->obj);
	if (!venus->IsDeleted())
	{
		LPGAMEOBJECT player = Game::GetInstance()->GetCurrentScene()->GetPlayer();
		dynamic_cast<Mario*>(player)->AddScore(x, y, 100);
		if (sfx == NULL)
		{
			float tmpx, tmpy;
			venus->GetPosition(tmpx, tmpy);
			sfx = new SFX(tmpx, tmpy, ID_ANI_VANISH);
			Game::GetInstance()->GetCurrentScene()->AddObject(sfx);
		}
		venus->Delete();
	}
}

void Tail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	Goomba* goomba = dynamic_cast<Goomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		LPGAMEOBJECT player = Game::GetInstance()->GetCurrentScene()->GetPlayer();
		dynamic_cast<Mario*>(player)->AddScore(x, y, 100);
		goomba->nx = e->nx;
		goomba->SetState(GOOMBA_STATE_DIE_UPSIDE_DOWN);
		if (sfx == NULL)
		{
			float tmpx, tmpy;
			goomba->GetPosition(tmpx, tmpy);
			sfx = new SFX(tmpx, tmpy, ID_ANI_HIT);
			Game::GetInstance()->GetCurrentScene()->AddObject(sfx);
		}
	}
}

void Tail::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
	koopa->SetDirection(e->nx);
	koopa->SetState(KOOPA_STATE_UPSIDE_DOWN);
	koopa->SetState(KOOPA_STATE_HIDE);
	if (sfx == NULL)
	{
		float tmpx, tmpy;
		koopa->GetPosition(tmpx, tmpy);
		sfx = new SFX(tmpx, tmpy, ID_ANI_HIT);
		Game::GetInstance()->GetCurrentScene()->AddObject(sfx);
	}
}

void Tail::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	QuestionBlock* qblock = dynamic_cast<QuestionBlock*>(e->obj);
	if (qblock->GetState() != QUESTION_BLOCK_STATE_HIT)
	{
		qblock->SetState(QUESTION_BLOCK_STATE_HIT);
	}
}

void Tail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TAIL_WIDTH / 2;
	t = y - TAIL_HEIGHT / 2;
	r = l + TAIL_WIDTH;
	b = t + TAIL_HEIGHT;
}
void Tail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(sfx != NULL)
		if (sfx->IsDeleted()) sfx = NULL;
	Collision::GetInstance()->Process(this, dt, coObjects);

}