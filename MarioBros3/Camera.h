#pragma once
#include <Windows.h>
#define CAMSPEED 0.02f


class Camera
{
	float cam_x = 0.0f;
	float cam_y = 0.0f;
	int width;
	int heigh;
public: 
	Camera(float x, float y, int width, int heigh)
	{
		cam_x = x; cam_y = y;
		this->width = width;
		this->heigh = heigh;
	}
	RECT GetBound();
	void Update(DWORD dt);
	bool IsContain(RECT objectBBox);
	bool IsContain(float x, float y);
	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }
};
