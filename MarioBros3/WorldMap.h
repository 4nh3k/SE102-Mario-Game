#pragma once
#include "Game.h"
#include "Scene.h"
#include "tileson.hpp"
#include "Tile.h"
#include "MapNode.h"
#include "HUD.h"

#define HUD_HEIGHT 36
#define HUD_POS_Y (176 + HUD_HEIGHT/2)
#define HUD_POS_X (16*8)

class WorldMap : public Scene
{
protected:
	HUD* hud;
	map<int, MapNode*> movingMap;
	BOOLEAN hasCreate;

	void LoadObjects(vector < tson::Object> objects);
	void LoadLayer(tson::Layer layer, tson::Vector2i tileSize);
	void InitMap();

public:
	WorldMap(int id, LPCWSTR filePath);

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

