#pragma once
#include "Game.h"
#include "Scene.h"
#include "tileson.hpp"
#include "Tile.h"
#include "MapNode.h"

#define HUD_HEIGHT 36
#define HUD_POS_Y (176 + HUD_HEIGHT/2)
#define HUD_POS_X (16*8)

class WorldMap : public Scene
{
protected:
	vector<Tile*> tileMap;
	LPGAMEOBJECT hud;
	map<int, MapNode*> movingMap;

	void LoadObjects(vector < tson::Object> objects);
	void LoadLayer(tson::Layer layer, tson::Vector2i tileSize);
	void LoadTileObjects(map<tuple<int, int>, tson::TileObject> tileObjects, tson::Vector2i tileSize);
	void LoadTilesets(vector<tson::Tileset> tileSets);
	void LoadAssets(LPCWSTR assetFile);
	void InitMap();

public:
	WorldMap(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void Clear();
	void PurgeDeletedObjects(std::deque<LPGAMEOBJECT>& list);
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

