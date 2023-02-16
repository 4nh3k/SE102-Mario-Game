#pragma once
#include "GameObject.h"
#include "MapNode.h"
#include "debug.h"

#define ANI_ID_SMALL_MARIO_MAP "small_mario_map"
#define ANI_ID_BIG_MARIO_MAP "big_mario_map"
#define ANI_ID_TANOOKI_MARIO_MAP "tanooki_mario_map"
#define MOVING_SPEED_X 0.1f
#define MOVING_SPEED_Y 0.1f

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TANOOKI	3


class MarioMap : public GameObject
{
	int directionX;
	int directionY;
	int nextNodeX;
	int nextNodeY;
	int level;
	BOOLEAN isMoving;
	MapNode* currentNode;
	void MoveToNextNode();
public:
	MarioMap(float x, float y);
	void Render();
	MapNode* GetCurrentNode();
	void SetLevel(int level);
	int GetLevel();
	void SetCurrentNode(MapNode* node);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	bool IsMoving();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking(float nx, float ny) { return 0; }
};

