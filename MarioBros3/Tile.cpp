#include "Tile.h"
void Tile::GetBoundingBox(LONG& l, LONG& t, LONG& r, LONG& b)
{
	l = x - this->width / 2;
	t = y - this->height / 2;
	r = l + this->width;
	b = t + this->height;
}
void Tile::Render()
{
	Sprites::GetInstance()->Get(spriteId)->Draw(x, y);
}
