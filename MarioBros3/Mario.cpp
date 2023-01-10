#include <algorithm>
#include "debug.h"
#include "Mario.h"
#include "Game.h"
#include "OneUpMushroom.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Coin.h"
#include "Portal.h"
#include "Mushroom.h"
#include "Collision.h"
#include "SuperLeaf.h"
#include "Laser.h"
#include "SFX.h"
#include "ParaGoomba.h"
#include "VenusFireTrap.h"

void Mario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((vx <= 0 && nx>0) || (vx >= 0 && nx < 0))
	{
		if (isSitting)
		{
			vx = 0;
			ax = 0;
		}
	}
	if (abs(vx) >= MARIO_RUNNING_SPEED && !startRunning)
	{
		startRunning = true;
		runTimer = GetTickCount64();
	}
	else
	{
		if(abs(vx)< MARIO_RUNNING_SPEED)
			startRunning = false;
	}
	if (GetTickCount64() - runTimer > MARIO_RUN_TIMEOUT && startRunning)
	{
		runTimer = 0;
		startRunning = false;
		isRunningFast = true;
	}
	if (abs(vx) > abs(maxVx) && !isSitting)
		vx = maxVx;

	if (GetTickCount64() - flyTimer > MARIO_FLY_TIMEOUT && isFlying)
	{
		flyTimer = 0;
		isFlying = false;
		//ay = MARIO_GRAVITY;
	}
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount64() - kickTimer > MARIO_KICK_TIMEOUT && isKicking)
	{
		kickTimer = 0;
		isKicking = false;
	}

	if (GetTickCount64() - tailTimer > MARIO_TAIL_WHACK_TIMEOUT && isTailWhack)
	{
		isTailWhack = false;
		// end tail whack delete tail
		if (tail != NULL)
		{
			tail->Delete();
			tail = NULL;
		}
	}
	isOnPlatform = false;
	//DebugOutTitle(L"x: %f,y: %f,vx: %f,vy: %f,ax: %f,ay: %f, isRunning: %d, isWalking: %d", x, y, vx, vy, ax, ay, isRunningFast, startRunning);
	DebugOutTitle(L"coin: %d, point: %d", coin, score);
	Collision::GetInstance()->Process(this, dt, coObjects);
	// set hold obj pos after x, y update
	TailUpdate();
	HoldingObjUpdate();
}

void Mario::TailUpdate()
{
	if (tail != NULL)
	{
		float tailx, taily;
		tail->GetPosition(tailx, taily);
		if (GetTickCount64() - tailTimer >= TAIL_CHANGE_SIDE_TIME)
			tail->SetPosition(x - MARIO_TAIL_OFFSET_X * nx, y + MARIO_TAIL_OFFSET_Y);
		else
			tail->SetPosition(x + MARIO_TAIL_OFFSET_X * nx, y + MARIO_TAIL_OFFSET_Y);
	}
}
void Mario::HoldingObjUpdate()
{
	if (isHolding)
	{
		int offsetX = (level == MARIO_LEVEL_TANOOKI) ? MARIO_TANOOKI_HOLDING_OFFSET_X : MARIO_HOLDING_OFFSET_X;
		if (vx == 0 || !isOnPlatform)
		{
			if (nx >= 0)
				holdingObj->SetPosition(x + offsetX, y - MARIO_HOLDING_OFFSET_Y);
			else
				holdingObj->SetPosition(x - offsetX, y - MARIO_HOLDING_OFFSET_Y);
		}
		else if (vx > 0)
		{
			holdingObj->SetPosition(x + offsetX, y - MARIO_HOLDING_OFFSET_Y);
		}
		else
		{
			holdingObj->SetPosition(x - offsetX, y - MARIO_HOLDING_OFFSET_Y);

		}
		if (holdingObj->GetState() == KOOPA_STATE_DIE)
		{
			isHolding = false;
			holdingObj = NULL;
		}
		else if (holdingObj->GetState() == KOOPA_STATE_WALKING)
		{
			isHolding = false;
			holdingObj = NULL;
			GetHitFromEnemy();
		}
	}
}

void Mario::OnNoCollision(DWORD dt)
{

	x += vx * dt;
	y += vy * dt;

}

void Mario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking(e->nx, e->ny))
	{
		vy = 0.0f;
		if (e->ny < 0)
		{
			// pull mario down, because to low gravity make it fail broad-phase test in collision 
			//vy = 0.015f;
			combo = 0;
			isOnPlatform = true;
		}
	}
	else 
		if (e->nx != 0 && e->obj->IsBlocking(e->nx, e->ny))
		{
			vx = 0;
		}
	if (dynamic_cast<Goomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<Coin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<Portal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<QuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<Mushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<Koopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<SuperLeaf*>(e->obj))
		OnCollisionWithSuperLeaf(e);
	else if (dynamic_cast<Laser*>(e->obj))
		OnCollisionWithLaser(e);
	else if (dynamic_cast<VenusFireTrap*>(e->obj))
		OnCollisionWithVenus(e);
}

void Mario::OnCollisionWithLaser(LPCOLLISIONEVENT e)
{
		GetHitFromEnemy();
}

void Mario::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	GetHitFromEnemy();
}

void Mario::OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e)
{
	SuperLeaf* superLeaf = dynamic_cast<SuperLeaf*>(e->obj);
	AddScore(x, y, 1000);
	if (level == MARIO_LEVEL_SMALL)
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
	else if (level == MARIO_LEVEL_BIG) {
		SetLevel(MARIO_LEVEL_TANOOKI);
	}
	superLeaf->Delete();
}

void Mario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
	if (koopa->GetState() == KOOPA_STATE_HIDE || koopa->GetState() == KOOPA_STATE_PICKED_UP)
	{
		float koopaX, koopaY;	
		koopa->GetPosition(koopaX,koopaY);
		if ((state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_RUNNING_RIGHT) && !isHolding)
		{
			isHolding = true;
			holdingObj = koopa;
			koopa->SetState(KOOPA_STATE_PICKED_UP);
		}
		else
		{
			if (isHolding && this->holdingObj == koopa) return;
			if (this->x > koopaX)
			{
				koopa->SetDirection(-1);
			}
			else
			{
				koopa->SetDirection(1);
			}
			if (isOnPlatform)
				this->SetState(MARIO_STATE_KICK);
			if(combo!=0)
				AddScore(x, y);
			koopa->SetState(KOOPA_STATE_KICKED);
		}
		return;
	}
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		AddScore(x, y);
		if (koopa->GetState() != KOOPA_STATE_HIDE)
		{
			koopa->SetState(KOOPA_STATE_HIDE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else 
	{
		if (koopa->GetState() != KOOPA_STATE_HIDE)
		{
			GetHitFromEnemy();
		}
	}
}

void Mario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	Mushroom* mushroom = dynamic_cast<Mushroom*>(e->obj);
	if (dynamic_cast<OneUpMushroom*>(e->obj))
	{
		AddScore(x, y, 0);
		mushroom->Delete();
		return;
	}
	if (level == MARIO_LEVEL_SMALL && mushroom->IsCollidable())
	{
		AddScore(x, y, 1000);
		mushroom->Delete();
		SetLevel(MARIO_LEVEL_BIG);
	}
}

void Mario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	QuestionBlock* qblock = dynamic_cast<QuestionBlock*>(e->obj);
	if (e->ny > 0)
	{
		if (qblock->GetState() != QUESTION_BLOCK_STATE_HIT)
		{ 
			qblock->SetState(QUESTION_BLOCK_STATE_HIT);
		}
	}
}

void Mario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	Goomba* goomba = dynamic_cast<Goomba*>(e->obj);
	if (dynamic_cast<ParaGoomba*>(e->obj))
	{
		OnCollisionWithParaGoomba(e);
		return;
	}
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			AddScore(x, y);
		}
	}
	else // hit by Goomba
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			GetHitFromEnemy();
		}
	}
}

void Mario::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	ParaGoomba* goomba = dynamic_cast<ParaGoomba*>(e->obj);
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			AddScore(x, y);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			if (goomba->HasWing())
			{
				goomba->SetWing(false);
				return;
			}
			goomba->SetState(GOOMBA_STATE_DIE);
		}
	}
	else // hit by Goomba
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			GetHitFromEnemy();
		}
	}
}

void Mario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	AddScore(x, y, 50);
	e->obj->Delete();
	coin++;
}

void Mario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	Portal* p = (Portal*)e->obj;
	Game::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void Mario::GetHitFromEnemy()
{
	if (untouchable != 0) return;
	if (level > MARIO_LEVEL_SMALL)
	{
		if (level == MARIO_LEVEL_TANOOKI)
		{
			SetLevel(MARIO_LEVEL_BIG);
		}
		else
		{
			SetLevel(MARIO_LEVEL_SMALL);
		}
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}
//
// Get animation ID for small Mario
//
string Mario::GetAniIdSmall()
{
	string aniId = "1";
	if (!isOnPlatform)
	{
		if (isHolding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_HOLD_LEFT;
		}
		else if (isRunningFast)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0)
					if (isHolding) aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else 
					if (isHolding) aniId = ID_ANI_MARIO_SMALL_IDLE_HOLD_LEFT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (isRunningFast)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				if (isHolding)
					aniId = ID_ANI_MARIO_SMALL_RUN_HOLD_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (isRunningFast)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				if (isHolding)
					aniId = ID_ANI_MARIO_SMALL_RUN_HOLD_LEFT;
			}
	if (isKicking)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
	}
	if (aniId == "1") aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
string Mario::GetAniIdBig()
{
	string aniId = "1";
	if (!isOnPlatform)
	{
		if (isHolding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_HOLD_LEFT;
		}
		else if (isRunningFast)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if(vy < 0)
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			else 
				if (nx >= 0)
					aniId = ID_ANI_MARIO_FALL_DOWN_RIGHT;
				else
					aniId = ID_ANI_MARIO_FALL_DOWN_LEFT;
		}
	}
	else 
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0)
				{
					if (isHolding) aniId = ID_ANI_MARIO_IDLE_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_RIGHT;
				}
				else
				{
					if (isHolding) aniId = ID_ANI_MARIO_IDLE_HOLD_LEFT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (isRunningFast)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
				if (isHolding)
					aniId = ID_ANI_MARIO_RUN_HOLD_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (isRunningFast)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else
					aniId = ID_ANI_MARIO_WALKING_LEFT;
				if (isHolding)
					aniId = ID_ANI_MARIO_RUN_HOLD_LEFT;
			}
	if (isKicking)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_KICK_LEFT;
	}
	if (state == MARIO_STATE_GROW_UP)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_GROW_UP_RIGHT;
		else aniId = ID_ANI_MARIO_GROW_UP_LEFT;
	}
	if (aniId == "1") aniId = ID_ANI_MARIO_IDLE_RIGHT;
	
	return aniId;
}

//
// Get animdation ID for tanooki Mario
//
string Mario::GetAniIdTanooki()
{
	string aniId = "1";
	if (!isOnPlatform)
	{
		if (isHolding)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_TANOOKI_JUMP_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANOOKI_JUMP_HOLD_LEFT;
		}
		else if (isRunningFast)
		{
			if (isFlying)
				if (nx >= 0)
					aniId = ID_ANI_MARIO_TANOOKI_FLY_RIGHT;
				else
					aniId = ID_ANI_MARIO_TANOOKI_FLY_LEFT;
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_TANOOKI_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_TANOOKI_JUMP_RUN_LEFT;
			}
		}
		else
		{
			if (isFlying)
				if (nx >= 0)
					aniId = ID_ANI_MARIO_TANOOKI_WALK_FLY_RIGHT;
				else
					aniId = ID_ANI_MARIO_TANOOKI_WALK_FLY_LEFT;
			else if (vy > 0)
				if (nx >= 0)
					aniId = ID_ANI_MARIO_TANOOKI_FALL_DOWN_RIGHT;
				else
					aniId = ID_ANI_MARIO_TANOOKI_FALL_DOWN_LEFT;
			else
				if (nx >= 0)
					aniId = ID_ANI_MARIO_TANOOKI_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_TANOOKI_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TANOOKI_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANOOKI_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0)
					if (isHolding) aniId = ID_ANI_MARIO_TANOOKI_IDLE_HOLD_RIGHT;
					else aniId = ID_ANI_MARIO_TANOOKI_IDLE_RIGHT;
				else
					if (isHolding) aniId = ID_ANI_MARIO_TANOOKI_IDLE_HOLD_LEFT;
					else aniId = ID_ANI_MARIO_TANOOKI_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_TANOOKI_BRACE_RIGHT;
				else 
					if (isRunningFast)
						aniId = ID_ANI_MARIO_TANOOKI_RUNNING_RIGHT;
					else
						aniId = ID_ANI_MARIO_TANOOKI_WALKING_RIGHT;
				if (isHolding)
					aniId = ID_ANI_MARIO_TANOOKI_RUN_HOLD_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_TANOOKI_BRACE_LEFT;
				else 
					if(isRunningFast)
						aniId = ID_ANI_MARIO_TANOOKI_RUNNING_LEFT;
					else
						aniId = ID_ANI_MARIO_TANOOKI_WALKING_LEFT;
				if (isHolding)
					aniId = ID_ANI_MARIO_TANOOKI_RUN_HOLD_LEFT;
			}
	if (isKicking)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_TANOOKI_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_TANOOKI_KICK_LEFT;
	}
	else if (isTailWhack)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_TANOOKI_TAIL_WHACK_RIGHT;
		else aniId = ID_ANI_MARIO_TANOOKI_TAIL_WHACK_LEFT;
	}
	if (aniId == "1") aniId = ID_ANI_MARIO_TANOOKI_IDLE_RIGHT;

	return aniId;
}

void Mario::Render()
{
	Animations* animations = Animations::GetInstance();
	string aniId = "1";
	if (!flickering && untouchable == 1)
	{
		flickering = true;
	}
	else if(flickering )
	{
		if (untouchable == 1)
		{
			flickering = false;
			return;
		}
		if (level == MARIO_LEVEL_TANOOKI)
		{
			return;
		}

	}
	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TANOOKI)
		aniId = GetAniIdTanooki();
	float xOffset = (level == MARIO_LEVEL_TANOOKI) ? 3 * -nx : 0;

	animations->Get(aniId)->Render(x + xOffset , y,false);

	RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %f, %f, %d", vx, ax, nx);
}

void Mario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 
	if (this->state == MARIO_STATE_GROW_UP && GetTickCount64() - changeFormTimer < MARIO_GROW_UP_TIMEOUT) return;
	else
	{
		if (this->state == MARIO_STATE_GROW_UP && GetTickCount64() - changeFormTimer > MARIO_GROW_UP_TIMEOUT)
		{
			Game::GetInstance()->GetCurrentScene()->Continue();
			flickering = false;
		}
	}


	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_HOLD_RIGHT:
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_RUNNING_HOLD_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_KICK:
		isKicking = true;
		if (holdingObj != NULL)
		{
			Koopa* koopa = dynamic_cast<Koopa*>(holdingObj);
			koopa->SetDirection(nx);
			koopa->SetState(KOOPA_STATE_KICKED);
			// null holding obj or else koopa will be kicked when u kick another koopa!!
			holdingObj = NULL;
		}
		isHolding = false;
		kickTimer = GetTickCount64();
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (level == MARIO_LEVEL_TANOOKI && !isOnPlatform)
		{
			SetState(MARIO_STATE_FLY);
			break;
		}
		if (isOnPlatform)	
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_FLY:
		if (isHolding) return;
		isFlying = true;
		flyTimer = GetTickCount64();
		if (isRunningFast)
			vy = -MARIO_FLY_SPEED_Y;
		else
			vy = MARIO_FALL_DONW_SPEED_Y;
	case MARIO_STATE_RELEASE_JUMP:
		// only pull down when not flying
		if (vy < 0 && !isFlying) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL && !isHolding)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			ax = (-nx) * MARIO_FRICTION;
			vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	case MARIO_STATE_TAIL_WHACK:
		if (isTailWhack) break;
		isTailWhack = true;
		tail = new Tail(x + MARIO_TAIL_OFFSET_X * nx,y + MARIO_TAIL_OFFSET_Y);
		Game::GetInstance()->GetCurrentScene()->AddObject(tail);
		tailTimer = GetTickCount64();
		break;
	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_RELEASE_RUN:
		isRunningFast = false;
		break;
	case MARIO_STATE_GROW_UP:
		changeFormTimer = GetTickCount64();
		break;
	}
	GameObject::SetState(state);
}
void Mario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG || level == MARIO_LEVEL_TANOOKI)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			// correct bounding box for tanooki
			left =(x ) - MARIO_BIG_BBOX_WIDTH/2 ;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

int Mario::CalcPoint(int combo)
{
	int point = 0;
	switch (combo)
	{
	case 1:
		point = 100;
		break;
	case 2:
		point = 200;
		break;
	case 3:
		point = 400;
		break;
	case 4:
		point = 800;
		break;
	case 5:
		point = 1000;
		break;
	case 6:
		point = 2000;
		break;
	case 7:
		point = 4000;
		break;
	case 8:
		point = 8000;
		break;
	default:
		break;
	}
	return point;
}

void Mario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		this->SetState(MARIO_STATE_GROW_UP);
		Game::GetInstance()->GetCurrentScene()->Pause();
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	if (l == MARIO_LEVEL_TANOOKI)
	{
		flickering = true;
		this->SetState(MARIO_STATE_GROW_UP);
		LPGAMEOBJECT sfx = new SFX(x, y, ID_ANI_VANISH);
		Game::GetInstance()->GetCurrentScene()->AddObject(sfx);
		Game::GetInstance()->GetCurrentScene()->Pause();
		
	}
	level = l;
}

