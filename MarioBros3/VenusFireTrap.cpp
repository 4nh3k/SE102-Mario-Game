#include "VenusFireTrap.h"
#include "Laser.h"
void VenusFireTrap::Render()
{
	string aniID;
	if(!moving)
		if (x > mx) // look left
		{
			if (y > my) // look up
			{
				aniID = ID_ANI_VENUS_IDLE_LEFT_UP;
			}
			else // look down
			{
				aniID = ID_ANI_VENUS_IDLE_LEFT_DOWN;
			}
		}
		else // look right
		{
			if (y > my)
			{
				aniID = ID_ANI_VENUS_IDLE_RIGHT_UP;
			}
			else
			{
				aniID = ID_ANI_VENUS_IDLE_RIGHT_DOWN;
			}
		}
	else
	{
		if (x > mx) // look left
		{
			if (y > my) // look up
			{
				aniID = ID_ANI_VENUS_CLOSE_LEFT_UP;
			}
			else // look down
			{
				aniID = ID_ANI_VENUS_CLOSE_LEFT_DOWN;
			}
		}
		else // look right
		{
			if (y > my)
			{
				aniID = ID_ANI_VENUS_CLOSE_RIGHT_UP;
			}
			else
			{
				aniID = ID_ANI_VENUS_CLOSE_RIGHT_DOWN;
			}
		}
	}
	Animations::GetInstance()->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}

void VenusFireTrap::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking(e->nx, e->ny)) return;

}

void VenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - VENUS_WIDTH / 2;
	t = y - VENUS_HEIGHT / 2;
	r = l + VENUS_WIDTH;
	b = t + VENUS_HEIGHT;
}
void VenusFireTrap::ShootLaser()
{
	LPGAMEOBJECT laser = new Laser(x, y + LASER_OFFSET_Y);
	int xDirection, yDirection;
	xDirection = (x < mx) ? 1 : -1;
	yDirection = (y < my) ? 1 : -1;
	int kq = abs(x - mx);
	if (kq > FAR_RANGE)
	{
		xDirection *= 2;
	}
	laser->SetSpeed(LASER_SPEED * xDirection, LASER_SPEED * yDirection);
	Game::GetInstance()->GetCurrentScene()->AddObject(laser);

}
void VenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (moving == true)
	{
		y += vy * dt;
	}
	if (oldY - y >= VENUS_HEIGHT && !isUp)
	{
		timer = GetTickCount64();
		moving = false;
		isUp = true;
	}
	/*if (y +VENUS_HEIGHT > oldY && !isUp)
	{
		timer = GetTickCount64();
		moving = false;
		isUp = true;
	}*/
	if (y >= oldY)
	{
		isDown = true;
		moving = false;
	}
	if (GetTickCount64() - timer > LASER_AIM_TIME && !hasShoot && isUp)
	{
		timer = GetTickCount64();
		ShootLaser();
		hasShoot = true;
	}
	else if (GetTickCount64() - timer > LASER_SHOOT_TIME && isUp)
	{
		vy = VENUS_SPEED;
		timer = GetTickCount64();
		isUp = false;		
		isDown = false;
		moving = true;
	}
	if (GetTickCount64() - timer > GO_DOWN_TIME)
	{
		moving = true;
		hasShoot = false;
		vy = (isUp) ? VENUS_SPEED : -VENUS_SPEED;
		isDown = false;
		timer = GetTickCount64();
	}
	//DebugOutTitle(L"x: %f, y:%f, vx:%f, vy: %f, moving: %d, isDown: %d, iscolliable: %d", x, y, vx, vy, moving, isDown, IsCollidable());
	Game::GetInstance()->GetCurrentScene()->GetPlayer()->GetPosition(mx,my);
}