#pragma once
#include "tileson.hpp"
#include "Tile.h"

class TileMap
{
	vector<Tile*> tileMap;
public:
	TileMap() {};
	void LoadTileObjects(map<tuple<int, int>, tson::TileObject> tileObjects, tson::Vector2i tileSize);
	void LoadTilesets(filesystem::path path, vector<tson::Tileset> tileSets);
	void Render();
	void Clear();
};

