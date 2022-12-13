#include "SuperLeaf.h"
#include "debug.h"
void SuperLeaf::Render()
{
	Animations* animations = Animations::GetInstance();
	if(vx<=0)
		animations->Get(ID_ANI_SUPER_LEAF_LEFT)->Render(x, y);
	else 
		animations->Get(ID_ANI_SUPER_LEAF_RIGHT)->Render(x, y);

	RenderBoundingBox();
}
void SuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	DebugOutTitle(L"x: %f, y: %f, vx: %f, vy: %f", x, y, vx, vy);
	if (y < oldY - SUPER_LEAF_RISE_UP_HEIGHT)
	{
		//ay = -SUPER_LEAF_GRAVITY;
		vy = SUPER_LEAF_FALL_DOWN_SPEED;
		vx = SUPER_LEAF_FALL_DOWN_SIDE_SPEED;

	}
	if (x > oldX + SUPER_LEAF_FALL_DOWN_WIDTH)
	{
		vx = -SUPER_LEAF_FALL_DOWN_SIDE_SPEED;
	}
	else if (x < oldX - SUPER_LEAF_FALL_DOWN_WIDTH)
	{
		vx = SUPER_LEAF_FALL_DOWN_SIDE_SPEED;
	}
}
void SuperLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SUPER_LEAF_BBOX_WIDTH / 2;
	t = y - SUPER_LEAF_BBOX_HEIGHT / 2;
	r = l + SUPER_LEAF_BBOX_WIDTH;
	b = t + SUPER_LEAF_BBOX_HEIGHT;
}