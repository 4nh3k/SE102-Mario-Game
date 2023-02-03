#pragma once
#include "GameObject.h"
#include "MapNode.h"
#include "debug.h"

#define ANI_ID_SMALL_MARIO_MAP "small_mario_map"
#define MOVING_SPEED_X 0.1f
#define MOVING_SPEED_Y 0.1f


class MarioMap : public GameObject
{
	int directionX;
	int directionY;
	int nextNodeX;
	int nextNodeY;
	BOOLEAN isMoving;
	MapNode* currentNode;
	void MoveToNextNode();
public:
	MarioMap(float x, float y);
	void Render();
	MapNode* GetCurrentNode();
	void SetCurrentNode(MapNode* node);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	bool IsMoving();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking(float nx, float ny) { return 0; }
};

