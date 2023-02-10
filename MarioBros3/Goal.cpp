#include "Goal.h"
Goal::Goal(float x, float y, float w, float h)
{
	hit = false;
	this->x = x;
	this->y = y;
	width = w;
	height = h;
}

void Goal::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	Game::GetInstance()->GetCamera()->GetCamPos(cx, cy);

	Game::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}
void Goal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (hit)
	{
		y += vy * dt;
	}
}
void Goal::Render()
{
	string aniId = ANI_ID_GOAL;
	if (hit)
	{
		switch (rewardId)
		{
		case 0:
			aniId = ANI_ID_FLOWER_ROTATE;
			break;
		case 1:
			aniId = ANI_ID_STAR_ROTATE;
			break;
		case 2:
			aniId = ANI_ID_MUSHROOM_ROTATE;
			break;
		default:
			break;
		}
	}
	Animations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
int Goal::GetReward()
{
	vy = -RAISE_UP_SPEED;
	hit = true;
	rewardId = Animations::GetInstance()->Get(ANI_ID_GOAL)->GetCurrentFrame();
	return rewardId;
}
void Goal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = x + width / 2;
	b = y + height / 2;
}