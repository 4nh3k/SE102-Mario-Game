#include "MarioMap.h"
void MarioMap::MoveToNextNode()
{
	if (nextNodeX != x || nextNodeY != y)
	{
		isMoving = true;
	}
	// neu = thi 0 di chuyen lon hon thi tang nho hon thi giam
	directionX = (nextNodeX == x) ? 0 : (nextNodeX > x) ? 1 : -1;
	directionY = (nextNodeY == y) ? 0 : (nextNodeY > y) ? 1 : -1;
	vx = directionX * MOVING_SPEED_X;
	vy = directionY * MOVING_SPEED_Y;
}
MarioMap::MarioMap(float x, float y) : GameObject(x, y) 
{
	currentNode = NULL;
	isMoving = false; 
	directionX = 0;
	directionY = 0;
}
void MarioMap::Render()
{
	Animations::GetInstance()->Get(ANI_ID_SMALL_MARIO_MAP)->Render(x, y);
}
MapNode* MarioMap::GetCurrentNode()
{
	return currentNode;
}
void MarioMap::SetCurrentNode(MapNode* node)
{
	currentNode = node;
	node->GetPos(nextNodeX, nextNodeY);
	MoveToNextNode();
}
void MarioMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isMoving)
	{
		x += vx * dt;
		y += vy * dt;
	}
	if ((x >= nextNodeX && directionX > 0) ||
		(x <= nextNodeX && directionX < 0) ||
		(y >= nextNodeY && directionY > 0) ||
		(y <= nextNodeY && directionY < 0))
	{
		x = nextNodeX;
		y = nextNodeY;
		vx = 0;
		vy = 0;
		isMoving = false;
	}

	DebugOutTitle(L"x: %f, y: %f, currentNodeId: %d", x, y, currentNode->GetId());
}
bool MarioMap::IsMoving()
{
	return isMoving;
}