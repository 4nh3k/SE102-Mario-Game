#include "PiranhaPlant.h"
void PiranhaPlant::Render()
{
	Animations::GetInstance()->Get(ID_ANI_PIRANHA_PLANT_IDLE)->Render(x, y);
	RenderBoundingBox();
}

void PiranhaPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIRANHA_PLANT_WIDTH / 2;
	t = y - PIRANHA_PLANT_HEIGHT / 2;
	r = l + PIRANHA_PLANT_WIDTH;
	b = t + PIRANHA_PLANT_HEIGHT;
}
void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (moving == true)
	{
		y += vy * dt;
	}
	if (oldY - y >= PIRANHA_PLANT_HEIGHT && !isUp)
	{
		timer = GetTickCount64();
		moving = false;
		isUp = true;
	}
	if (y >= oldY)
	{
		isDown = true;
		moving = false;
	}
	if (GetTickCount64() - timer > GO_UP_TIME & isUp)
	{
		moving = true;
		isUp = false;
		vy = PIRANHA_PLANT_SPEED;
		timer = GetTickCount64();
	}
	if (GetTickCount64() - timer > GO_DOWN_TIME & isDown)
	{
		moving = true;
		vy = (isUp) ? PIRANHA_PLANT_SPEED : -PIRANHA_PLANT_SPEED;
		isDown = false;
		timer = GetTickCount64();
	}
	//DebugOutTitle(L"x: %f, y:%f, vx:%f, vy: %f, moving: %d, isDown: %d, isUp: %d, iscolliable: %d", x, y, vx, vy, moving, isDown, isUp, IsCollidable());

}