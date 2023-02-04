#pragma once
#include "Game.h"
#include "Scene.h"
#include "tileson.hpp"
#include "Tile.h"
#include "MapNode.h"
#include "HUD.h"

class IntroScene : public Scene
{
protected:
	vector<Tile*> tileMap;

	void LoadObjects(vector < tson::Object> objects);
	void LoadLayer(tson::Layer layer, tson::Vector2i tileSize);
	void LoadTileObjects(map<tuple<int, int>, tson::TileObject> tileObjects, tson::Vector2i tileSize);
	void LoadTilesets(vector<tson::Tileset> tileSets);
	void LoadAssets(LPCWSTR assetFile);

public:
	IntroScene(int id, LPCWSTR filePath);

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

