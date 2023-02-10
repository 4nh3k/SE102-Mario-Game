#pragma once
#include "Game.h"
#include "Scene.h"
#include "tileson.hpp"
#include "Tile.h"

#define WORLD_MAP_SCENE_ID 2

#define ID_ANI_NUMBER3	"intro_3"
#define ID_ANI_CURSOR	"cursor"
#define NUMBER3_POS_X	136
#define NUMBER3_POS_Y	120
#define CURSOR_POS_X	76
#define CURSOR_POS_Y_1	148
#define CURSOR_POS_Y_2	164


class IntroScene : public Scene
{
protected:
	float cursorY;

	void LoadObjects(vector < tson::Object> objects);
	void LoadLayer(tson::Layer layer, tson::Vector2i tileSize);

public:
	IntroScene(int id, LPCWSTR filePath);

	void MoveCursor();
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual int GetBackGroundColor() { return BLACK_BACKGROUND_ID; }

	void Clear();
	void PurgeDeletedObjects(std::deque<LPGAMEOBJECT>& list);
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

