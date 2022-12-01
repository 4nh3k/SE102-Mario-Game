#pragma once
#include <Windows.h>
class Camera
{
	float cam_x = 0.0f;
	float cam_y = 0.0f;
	float width;
	float heigh;
public: 
	Camera(float x, float y, float width, float heigh)
	{
		cam_x = x; cam_y = y;
		this->width = width;
		this->heigh = heigh;
	}
	RECT GetBound();
	bool IsContain(RECT objectBBox);
	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }
};
