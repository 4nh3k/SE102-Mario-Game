#include "ParaGoomba.h"
void ParaGoomba::Render()
{
	string aniId = ID_ANI_PARA_GOOMBA_WALKING;
	if (isOnPlatform && hasWing)
	{
		aniId = ID_ANI_PARA_GOOMBA_WING_CLOSE;
	}
	else if (isOnPlatform && !hasWing)
		aniId = ID_ANI_PARA_GOOMBA_WALKING;
	else if (!isOnPlatform && hasWing)
		aniId = ID_ANI_PARA_GOOMBA_FLY;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARA_GOOMBA_DIE;
	}
	else if (state == GOOMBA_STATE_DIE_UPSIDE_DOWN)
	{
		aniId = ID_ANI_PARA_GOOMBA_DIE_UPSIDE_DOWN;
	}
	Animations::GetInstance()->Get(aniId)->Render(x, y);

}
void ParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (GetTickCount64() - timer >= PARA_GOOMBA_WALK_TIMEOUT && !isFlying)
	{
		isFlying = true;
	}
	if (jumpCount < PARA_GOOMBA_SMALL_JUMP_LIMIT && isOnPlatform && isFlying && hasWing)
	{
		vy = -PARA_GOOMBA_SMALL_JUMP_SPEED_Y;
		jumpCount++;
	}
	else
	{
		if (jumpCount >= PARA_GOOMBA_SMALL_JUMP_LIMIT && isOnPlatform && isFlying && hasWing)
		{
			jumpCount = 0;
			isFlying = false;
			timer = GetTickCount64();
			vy = -PARA_GOOMBA_FLY_SPEED_Y;
		}
	}
	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	isOnPlatform = false;
	Collision::GetInstance()->Process(this, dt, coObjects);
}