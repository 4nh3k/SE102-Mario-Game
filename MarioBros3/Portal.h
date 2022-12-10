#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class Portal : public GameObject
{
	int scene_id;	// target scene to switch to 
	int rewardId;
	float width;
	float height; 
public:
	Portal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	LPGAMEOBJECT GetReward(int rewardId);
	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking(float nx, float ny) { return 0; }
};