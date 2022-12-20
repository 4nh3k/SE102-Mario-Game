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
	DebugOutTitle(L"nx: %f, ny: %f", e->nx, e->ny);

}

void VenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 10 / 2;
	t = y - 10 / 2;
	r = l + 10;
	b = t + 10;
}
void VenusFireTrap::ShootLaser()
{
	LPGAMEOBJECT laser = new Laser(x, y);
	int xDirection, yDirection;
	xDirection = (x < mx) ? 1 : -1;
	yDirection = (y < my) ? 1 : -1;
	int kq = abs(x - mx);
	if (kq > 80)
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
	DebugOutTitle(L"y: %f oldY: %f, H: %d", y, oldY, VENUS_HEIGHT);
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
		vy = -vy;
		timer = GetTickCount64();
		isUp = false;
		moving = true;
	}
	if (GetTickCount64() - timer > GO_DOWN_TIME)
	{
		moving = true;
		hasShoot = false;
		vy = (isUp) ? 0.03f : -0.03f;
		timer = GetTickCount64();
	}
	Game::GetInstance()->GetCurrentScene()->GetPlayer()->GetPosition(mx,my);
}