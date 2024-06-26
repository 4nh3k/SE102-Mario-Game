#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

//void Platform::RenderBoundingBox()
//{
//	D3DXVECTOR3 p(x, y, 0);
//	RECT rect;
//
//	LPTEXTURE bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);
//
//	float l, t, r, b;
//
//	GetBoundingBox(l, t, r, b);
//	rect.left = 0;
//	rect.top = 0;
//	rect.right = (int)r - (int)l;
//	rect.bottom = (int)b - (int)t;
//
//	float cx, cy;
//	Game::GetInstance()->GetCamPos(cx, cy);
//
//	float xx = x+ rect.right / 2;
//
//	Game::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
//}

void Platform::Render()
{
	/*if (this->length <= 0) return; 
	float xx = x; 
	Sprites * s = Sprites::GetInstance();

	s->Get(this->spriteIdBegin)->Draw(xx, y);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw(xx, y);
		xx += this->cellWidth;
	}
	if (length>1)
		s->Get(this->spriteIdEnd)->Draw(xx, y);*/

	RenderBoundingBox();
}

void Platform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width/2;
	t = y - this->height /2;
	r = l + this->width;
	b = t + this->height;
}