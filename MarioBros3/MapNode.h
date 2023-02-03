#pragma once

#define NULL 0

#define ANI_ID_WORLD_1 "world1"
#define WORD_1_SCENE_ID 2
#define ANI_ID_WORLD_CLEAR "world_clear"

class MapNode
{
	int id;
	int x, y;
	int l, r, t, b;
	int scene_id;
	bool hasClear;
public: 
	MapNode* Left;
	MapNode* Right;
	MapNode* Bot;
	MapNode* Top;
	MapNode(int id, int x, int y, int left, int right, int top, int bot, int scene_id);
	void GetNextNode(int& l, int& r, int& t, int& b);
	int GetSceneId();
	void SetClear(bool clear);
	bool HasClear();
	int GetId();
	void GetPos(int& x, int& y);
	void Render();
};

