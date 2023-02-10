#include "MapNode.h"
#include "Animations.h"

MapNode::MapNode(int id, int x, int y, int left, int right, int top, int bot, int scene_id)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->l = left;
	this->r = right;
	this->t = top;
	this->b = bot;
	this->scene_id = scene_id;
	hasClear = false;
	Left = NULL;
	Right = NULL;
	Bot = NULL;
	Top = NULL;
}
int MapNode::GetSceneId()
{
	return scene_id;
}
void MapNode::GetNextNode(int& l, int& r, int& t, int& b)
{
	l = this->l;
	r = this->r;
	b = this->b;
	t = this->t;
}
void MapNode::GetPos(int& x, int& y)
{
	x = this->x;
	y = this->y;
}
void MapNode::SetClear(bool clear)
{
	hasClear = clear;
}
bool MapNode::HasClear()
{
	if (scene_id < 0)
	{
		hasClear = true;
	}
	return hasClear;
}
int MapNode::GetId()
{
	return this->id;
}
void MapNode::Render()
{
	if (scene_id < 0) return;
	if (hasClear)
	{
		Animations::GetInstance()->Get(ANI_ID_WORLD_CLEAR)->Render(x, y);
		return;
	}

	//Animations::GetInstance()->Get(ANI_ID_WORLD_1)->Render(x, y);
}