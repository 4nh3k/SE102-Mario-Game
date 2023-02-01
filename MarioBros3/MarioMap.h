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
	void MoveToNextNode()
	{
		if(nextNodeX != x || nextNodeY!=y)
			isMoving = true;
		// neu = thi 0 di chuyen lon hon thi tang nho hon thi giam
		directionX = (nextNodeX == x) ? 0 : (nextNodeX > x) ? 1 : -1;
		directionY = (nextNodeY == y) ? 0 : (nextNodeY > y) ? 1 : -1;
		vx = directionX * MOVING_SPEED_X;
		vy = directionY * MOVING_SPEED_Y;
	}
public:
	MarioMap(float x, float y) : GameObject(x, y) { currentNode = NULL; isMoving = false; directionX = 0; directionY = 0; }
	void Render() {
		Animations::GetInstance()->Get(ANI_ID_SMALL_MARIO_MAP)->Render(x, y);
	}
	MapNode* GetCurrentNode()
	{
		return currentNode;
	}
	void SetCurrentNode(MapNode* node)
	{
		currentNode = node;
		node->GetPos(nextNodeX, nextNodeY);
		MoveToNextNode();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (isMoving)
		{
			x += vx * dt;
			y += vy * dt;
		}
		if ((x>=nextNodeX && directionX > 0) || 
			(x<=nextNodeX && directionX < 0) || 
			(y >= nextNodeY && directionY > 0) ||
			(y <= nextNodeY && directionY < 0))
		{
			x = nextNodeX;
			y = nextNodeY;
			vx = 0;
			vy = 0;
			isMoving = false;
		}
		
		DebugOutTitle(L"x: %f, y: %f, currentNodeId: %d",x, y, currentNode->GetId());
	}
	bool IsMoving()
	{
		return isMoving;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking(float nx, float ny) { return 0; }
};

