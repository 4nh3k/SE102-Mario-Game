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
#include "PSwitch.h"
#include "Brick.h"
#include "PiranhaPlant.h"
#include "ParaKoopa.h"
#include "Pipeline.h"
#include "MomentumBar.h"
#include "Goal.h"
#include "TheVoid.h"
#include "HUD.h"
#include "MarioCollisionVisitor.h"
#include "PlayScene.h"

Mario::Mario(float x, float y) : GameObject(x, y)
{
	isSitting = false;
	maxVx = 0.0f;
	ax = 0.0f;
	ay = MARIO_GRAVITY;
	holdingObj = NULL;
	isHolding = false;
	isRunningFast = false;
	isFlying = false;
	isOnPlatform = false;
	isKicking = false;
	isTailWhack = false;
	flickering = false;
	isPressUp = false;
	hasFinish = false;
	flyTimer = 0;
	kickTimer = 0;
	tailTimer = 0;
	combo = 0;
	runTimer = -1;
	changeFormTimer = 0;
	level = MARIO_LEVEL_SMALL;
	tail = NULL;
	untouchable = 0;
	untouchable_start = -1;
}
// Copy Constructor
Mario::Mario(const Mario& other)
	: GameObject(other), // Call base class copy constructor if needed
	isSitting(other.isSitting),
	isOnPlatform(other.isOnPlatform),
	isHolding(other.isHolding),
	isKicking(other.isKicking),
	isTailWhack(other.isTailWhack),
	isFlying(other.isFlying),
	isRunningFast(other.isRunningFast),
	flickering(other.flickering),
	isPressUp(other.isPressUp),
	hasFinish(other.hasFinish),
	teleporting(other.teleporting),
	teleDirection(other.teleDirection),
	oldY(other.oldY),
	teleX(other.teleX),
	teleY(other.teleY),
	teleCamX(other.teleCamX),
	teleCamY(other.teleCamY),
	teleColor(other.teleColor),
	maxVx(other.maxVx),
	ax(other.ax),
	ay(other.ay),
	kickTimer(other.kickTimer),
	flyTimer(other.flyTimer),
	tailTimer(other.tailTimer),
	runTimer(other.runTimer),
	deadTimer(other.deadTimer),
	untouchable_start(other.untouchable_start),
	changeFormTimer(other.changeFormTimer),
	combo(other.combo),
	level(other.level),
	preLevel(other.preLevel),
	untouchable(other.untouchable),
	holdingObj(other.holdingObj ? other.holdingObj->Clone() : nullptr),
	tail(other.tail ? other.tail->Clone() : nullptr) {
	// Deep copy any dynamically allocated members if needed
}

// Clone method
GameObject* Mario::Clone() {
	return new Mario(*this); // Use the copy constructor
}

int Mario::IsCollidable() 
{
	return (state != MARIO_STATE_DIE);
}
BOOLEAN Mario::HasFinish()
{
	return hasFinish;
}
int Mario::IsBlocking(float nx, float ny) 
{ 
	return (state != MARIO_STATE_DIE && untouchable == 0);
}

BOOLEAN Mario::IsGoingPipeLine()
{
	return teleporting;
}

void Mario::SetUpKey(bool keyDown)
{
	this->isPressUp = keyDown;
}

int Mario::IsFlying()
{
	return (level == MARIO_LEVEL_TANOOKI && MomentumBar::GetInstance()->GetNode() == MOMENTUM_NODE_COUNT); 
}

int Mario::IsOnPlatform()
{
	return isOnPlatform;
}

int Mario::IsTanooki()
{
	return (level == MARIO_LEVEL_TANOOKI);
}

int Mario::GetLevel()
{
	return level;
}
void Mario::AddCoin()
{
	HUD::GetInstance()->AddCoin();
}

void Mario::AddScore(float Px, float Py, int point)
{
	HUD::GetInstance()->AddScore(point);
	Game::GetInstance()->GetCurrentScene()->AddSFX(new PointSFX(Px, Py, PointSFX::GetAniId(point)));
}

void Mario::AddScore(float Px, float Py) {
	combo++;
	int point = CalcPoint(combo);
	AddScore(Px, Py, point);
}

BOOLEAN Mario::IsHolding()
{
	return (isHolding && !holdingObj->IsDeleted());
}

void Mario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (teleporting)
	{
		// if mario issitting then go down?
		vy = MARIO_GO_DOWN_SPEED_Y * teleDirection;
		y += vy * dt;
		DebugOutTitle(L"x: %f,y: %f,vx: %f,vy: %f,ax: %f,ay: %f, isRunningFast: %d, isFlying: %d, isSitting: %d, isPressUp: %d", x, y, vx, vy, ax, ay, isRunningFast, isFlying, isSitting, isPressUp);

		if (abs(oldY - y) > MARIO_BIG_BBOX_HEIGHT && oldY != teleY)
		{
			Game::GetInstance()->GetCurrentScene()->SetBackGroundColor(teleColor);
			Game::GetInstance()->GetCurrentScene()->SetCamLimitPos(teleCamX, teleCamY);
			x = teleX;
			y = teleY;
			oldY = y;
		}
		if (oldY == teleY && abs(oldY - y) > MARIO_BIG_BBOX_HEIGHT)
		{
			teleporting = false;
		}
	}

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
	if (abs(vx) > abs(maxVx) && !isSitting)
		vx = maxVx;
	if (abs(vx) > MARIO_WALKING_SPEED)
	{
		int tmp = (((abs(vx) - MARIO_WALKING_SPEED) / (MARIO_RUNNING_SPEED - MARIO_WALKING_SPEED)) * 6);
		isRunningFast = (tmp == 6) ? true : false;
		//DebugOutTitle(L"vx: %f, ax: %f, tmp: %d", vx, ax, tmp);
		MomentumBar::GetInstance()->SetNode(tmp);
	}
	else {
		MomentumBar::GetInstance()->Decrease();
	}

	if (GetTickCount64() - flyTimer > MARIO_FLY_TIMEOUT && isFlying)
	{
		flyTimer = 0;
		isFlying = false;
		//ay = MARIO_GRAVITY;
	}

	if (GetTickCount64() - deadTimer > MARIO_DEAD_TIMEOUT && state == MARIO_STATE_DIE)
	{
		PlayScene* scene = dynamic_cast<PlayScene*>(Game::GetInstance()->GetCurrentScene());
		if (scene != nullptr) {
			// The cast was successful and you can now work with the PlayScene object.
			scene->Undo();
		}
		else {
			// The cast failed, handle the error accordingly.
			Game::GetInstance()->InitiateSwitchScene(WORLD_MAP_ID);
			Game::GetInstance()->SwitchScene();
		}
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
	//DebugOutTitle(L"x: %f,y: %f,vx: %f,vy: %f,ax: %f,ay: %f, isRunningFast: %d, isFlying: %d, isSitting: %d, isPressUp: %d", x, y, vx, vy, ax, ay, isRunningFast, isFlying, isSitting, isPressUp);
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
	// stop moving while go down pipeline
	if (!teleporting)
	{
		x += vx * dt;
		y += vy * dt;
	}

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
			if (hasFinish) SetState(MARIO_STATE_WALKING_RIGHT);
		}
	}
	else 
		if (e->nx != 0 && e->obj->IsBlocking(e->nx, e->ny))
		{
			vx = 0;
		}
	CollisionVisitor* visitor = new MarioCollisionVisitor(this, e);
	e->obj->Accept(visitor);
}

void Mario::OnCollisionWithTheVoid(LPCOLLISIONEVENT e)
{
	SetState(MARIO_STATE_DIE);
}

void Mario::OnCollisionWithPipeline(LPCOLLISIONEVENT e)
{
	Pipeline* pipe = dynamic_cast<Pipeline*>(e->obj);
	if ((e->ny < 0 && (this->state == MARIO_STATE_SIT || isSitting)) || (e->ny > 0 && isPressUp))
	{
		teleColor = pipe->GetBackGroundColor();
		HUD::GetInstance()->StopTimer();
		teleDirection = (isPressUp) ? -1 : 1;
		// do it like this because collision push back set it back to old pos
		oldY = y;
		pipe->GetTelePos(x, y);
		pipe->GetCamPos(teleCamX, teleCamY);
		teleX = x;
		teleY = y;
		teleporting = true;
	}
}

void Mario::OnCollisionWithGoal(LPCOLLISIONEVENT e)
{
	Goal* goal = dynamic_cast<Goal*>(e->obj);
	if (!goal->HasHit())
	{
		float msgX, msgY;
		goal->GetPosition(msgX, msgY);
		string tmp = "course clear !";
		LPGAMEOBJECT mssg = new Font(msgX - (tmp.size()*FONT_WIDTH/2), msgY - COURSE_CLEAR_OFFSET_Y, -1);
		dynamic_cast<Font*>(mssg)->SetString(tmp);
		Game::GetInstance()->GetCurrentScene()->AddSFX(mssg);
		tmp = "you got a card  ";
		mssg = new Font(msgX - (tmp.size() * FONT_WIDTH / 2), msgY - GOT_A_CARD_OFFSET_Y, -1);
		dynamic_cast<Font*>(mssg)->SetString(tmp);
		Game::GetInstance()->GetCurrentScene()->AddSFX(mssg);
		mssg = new Card(msgX + (tmp.size() * FONT_WIDTH / 2), msgY - GOT_A_CARD_OFFSET_Y, goal->GetReward());
		Game::GetInstance()->GetCurrentScene()->AddSFX(mssg);
		hasFinish = true;
		SetState(MARIO_STATE_IDLE);
		HUD::GetInstance()->AddCard(goal->GetReward());
		HUD::GetInstance()->FinishScene();
	}
	DebugOut(L"\n%d", goal->GetReward());
}

void Mario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	GetHitFromEnemy();
}

void Mario::OnCollisionWithPSwitch(LPCOLLISIONEVENT e)
{
	PSwitch* pSwitch = dynamic_cast<PSwitch*>(e->obj);
	if (pSwitch->GetState() == PSWITCH_STATE_IDLE && e->ny < 0)
	{
		pSwitch->SetState(PSWITCH_STATE_HIT);
	}
}

void Mario::OnCollisionWithLaser(LPCOLLISIONEVENT e)
{
	GetHitFromEnemy();
}

void Mario::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	GetHitFromEnemy();
}

void Mario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	Brick* brick = dynamic_cast<Brick*>(e->obj);
	if (e->ny > 0)
	{
		if (!brick->IsDeleted())
		{
			brick->Break();
		}
	}
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
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		if (dynamic_cast<ParaKoopa*>(e->obj))
		{
			ParaKoopa* paraKoopa = dynamic_cast<ParaKoopa*>(e->obj);
			if (paraKoopa->HasWing())
			{
				paraKoopa->SetWing(false);
				return;
			}
		}
		if (koopa->GetState() != KOOPA_STATE_HIDE)
		{
			koopa->SetState(KOOPA_STATE_HIDE);
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
		HUD::GetInstance()->AddLife(1);
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
	AddCoin();
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
		Game::GetInstance()->GetCurrentScene()->Pause();
		this->SetState(MARIO_STATE_CHANGE_FORM);
		if (level == MARIO_LEVEL_TANOOKI)
		{
			flickering = true;
			LPGAMEOBJECT sfx = new SFX(x, y, ID_ANI_VANISH);
			Game::GetInstance()->GetCurrentScene()->AddSFX(sfx);
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
	if (state == MARIO_STATE_CHANGE_FORM)
	{
		if (nx > 0) aniId = ID_ANI_MARIO_GROW_UP_RIGHT;
		else aniId = ID_ANI_MARIO_GROW_UP_LEFT;
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
	if (state == MARIO_STATE_CHANGE_FORM && preLevel < level)
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
	int node = MomentumBar::GetInstance()->GetNode();
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
		else if (node == MOMENTUM_NODE_COUNT)
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
	else if (teleporting) aniId = ID_ANI_MARIO_GO_DOWN;
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
	else if(flickering)
	{
		if (untouchable == 1)
		{
			flickering = false;
			return;
		}
		if (level == MARIO_LEVEL_TANOOKI)
		{
			if(Game::GetInstance()->GetCurrentScene()->IsPause())
				return;
			flickering = false;
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
	if (this->state == MARIO_STATE_CHANGE_FORM && GetTickCount64() - changeFormTimer < MARIO_GROW_UP_TIMEOUT) return;
	else
	{
		if (this->state == MARIO_STATE_CHANGE_FORM && GetTickCount64() - changeFormTimer > MARIO_GROW_UP_TIMEOUT)
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
		ax = ((abs(vx) > MARIO_WALKING_SPEED) && vx >0) ? MARIO_ACCEL_RUN_X : MARIO_ACCEL_WALK_X;
		//ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_HOLD_RIGHT:
		maxVx = MARIO_RUNNING_SPEED;
		ax = ((abs(vx) > MARIO_WALKING_SPEED) && vx>0) ? MARIO_ACCEL_RUN_X : MARIO_ACCEL_WALK_X;
		//ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = ((abs(vx) > MARIO_WALKING_SPEED) && vx < 0) ? -MARIO_ACCEL_RUN_X : -MARIO_ACCEL_WALK_X;
		//ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_RUNNING_HOLD_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = ((abs(vx) > MARIO_WALKING_SPEED) && vx < 0) ? -MARIO_ACCEL_RUN_X : -MARIO_ACCEL_WALK_X;
		//ax = -MARIO_ACCEL_WALK_X;
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
		if(isRunningFast)	MomentumBar::GetInstance()->IndiactorFull();
		if (MomentumBar::GetInstance()->GetNode() == 6)
		{
			vy = -MARIO_FLY_SPEED_Y;
		}
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
		HUD::GetInstance()->DecreseLife();
		deadTimer = GetTickCount64();
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_RELEASE_RUN:
		isRunningFast = false;
		break;
	case MARIO_STATE_CHANGE_FORM:
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

void Mario::SetLevel(int l, bool pause)
{
	preLevel = level;
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		if (pause)
		{
			this->SetState(MARIO_STATE_CHANGE_FORM);
			Game::GetInstance()->GetCurrentScene()->Pause();
		}
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	if (l == MARIO_LEVEL_TANOOKI && pause)
	{
		flickering = true;
		this->SetState(MARIO_STATE_CHANGE_FORM);
		LPGAMEOBJECT sfx = new SFX(x, y, ID_ANI_VANISH);
		Game::GetInstance()->GetCurrentScene()->AddSFX(sfx);
		Game::GetInstance()->GetCurrentScene()->Pause();
	}
	level = l;
}

