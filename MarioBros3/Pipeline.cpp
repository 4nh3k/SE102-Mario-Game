#include "Pipeline.h"
Pipeline::Pipeline(float x, float y, float width, float height, float targetX, float targetY, float camX, float camY, int backgroundId)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->targetX = targetX;
	this->targetY = targetY;
	this->camX = camX;
	this->camY = camY;
	this->backgroundId = backgroundId;
}

void Pipeline::RenderBoundingBox()
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

void Pipeline::Render()
{
	RenderBoundingBox();
}
void Pipeline::GetTelePos(float& x, float& y)
{
	x = this->targetX;
	y = this->targetY;
}

int Pipeline::GetBackGroundColor()
{
	return this->backgroundId;
}

void Pipeline::GetCamPos(float& camX, float& camY)
{
	camX = this->camX;
	camY = this->camY;
}

void Pipeline::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = x + width / 2;
	b = y + height / 2;
}