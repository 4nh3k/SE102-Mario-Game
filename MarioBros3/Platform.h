#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class Platform : public GameObject
{
protected: 
	float width;
	float height;

public: 
	Platform(float x, float y,
		float width, float height) :GameObject(x, y)
	{
		this->width = width;
		this->height = height;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	//void RenderBoundingBox();
};

typedef Platform* LPPLATFORM;