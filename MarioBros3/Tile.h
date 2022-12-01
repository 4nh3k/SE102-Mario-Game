#pragma once
#include "GameObject.h"
#include "Sprites.h"
class Tile : public GameObject
{
protected:
	string spriteId;
	float width;
	float height;

public:
	Tile(float x, float y, float width, float height,
		string spriteId) : GameObject(x, y)
	{
		this->width = width;
		this->height = height;
		this->spriteId = spriteId;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void GetBoundingBox(LONG& l, LONG& t, LONG& r, LONG& b);
	//void RenderBoundingBox();
};

