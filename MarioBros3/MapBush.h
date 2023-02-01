#pragma once
#include "GameObject.h"
#include "Animations.h"
#define ANI_ID_MAP_BUSH "map_bush"
class MapBush : public GameObject 
{	
public:
	MapBush(float x, float y) : GameObject(x, y) {}
	void Render()
	{
		Animations::GetInstance()->Get(ANI_ID_MAP_BUSH)->Render(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking(float nx, float ny) { return 0; }
};

