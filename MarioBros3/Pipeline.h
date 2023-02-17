#pragma once
#include "GameObject.h"
class Pipeline :
    public GameObject
{
	float targetX;
	float targetY;	// target pos to teleport to 
	float camX;
	float camY;
	float width;
	float height;
	int backgroundId;
public:
	Pipeline(float x, float y, float width, float height, float targetX, float targetY, float camX, float camY, int backgroundId);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void GetTelePos(float& x, float& y);
	void GetCamPos(float& camX, float& camY);
	int GetBackGroundColor();
	void RenderBoundingBox();
	int IsBlocking(float nx, float ny) { return 1; }
};

