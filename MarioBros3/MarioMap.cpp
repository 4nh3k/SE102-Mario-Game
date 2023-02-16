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
	level = MARIO_LEVEL_SMALL;
	currentNode = NULL;
	isMoving = false; 
	directionX = 0;
	directionY = 0;
}
void MarioMap::Render()
{
	string aniId = ANI_ID_SMALL_MARIO_MAP;
	switch (level)
	{
	case MARIO_LEVEL_BIG:
		aniId = ANI_ID_BIG_MARIO_MAP;
		break;
	case MARIO_LEVEL_TANOOKI:
		aniId = ANI_ID_TANOOKI_MARIO_MAP;
		break;
	default:
		break;
	}
	Animations::GetInstance()->Get(aniId)->Render(x, y);
}
void MarioMap::SetLevel(int level)
{
	this->level = level;
}
int MarioMap::GetLevel()
{
	return level;
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