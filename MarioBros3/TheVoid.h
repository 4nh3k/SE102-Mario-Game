#pragma once
#include "GameObject.h"
class TheVoid :
    public GameObject
{
	float width;
	float height;
public:
	TheVoid(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		width = w;
		height = h;
	}
	virtual void Render()
	{
		RenderBoundingBox();
	}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - width / 2;
		t = y - height / 2;
		r = x + width / 2;
		b = y + height / 2;
	}

	int IsBlocking(float nx, float ny) { return 0; }	
};

