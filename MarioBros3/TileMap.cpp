#include "TileMap.h"

void TileMap::LoadTileObjects(map<tuple<int, int>, tson::TileObject> tileObjects, tson::Vector2i tileSize)
{
	for (auto& [pos, tileObject] : tileObjects)
	{
		tson::Vector2f position = tileObject.getPosition();
		string tileId = to_string(tileObject.getTile()->getGid());
		// position + tileSize/2 because the difference between tiled map x, y and this game x,y
		Tile* tile = new Tile(position.x + tileSize.x / 2, position.y + tileSize.y / 2,
			tileSize.x, tileSize.y, tileId);
		tileMap.push_back(tile);
	}
}
void TileMap::LoadTilesets(filesystem::path path, vector<tson::Tileset> tileSets)
{
	for (auto& tileSet : tileSets)
	{
		string image = tileSet.getImagePath().u8string();

		// Get directory then append image file name
		path = path.parent_path() / image;
		Textures::GetInstance()->Add(image, path.c_str());
		for (auto& tile : tileSet.getTiles())
		{
			tson::Rect drawingRect = tile.getDrawingRect();
			Sprites::GetInstance()->Add(
				to_string(tile.getGid()),
				drawingRect.x, drawingRect.y,
				drawingRect.x + drawingRect.width, drawingRect.y + drawingRect.height,
				Textures::GetInstance()->Get(image)
			);
		}
	}
}
void TileMap::Render()
{
	for (auto& tile : tileMap)
	{
		RECT rect;
		tile->GetBoundingBox(rect.left, rect.top, rect.right, rect.bottom);
		if (Game::GetInstance()->GetCamera()->IsContain(rect))
			tile->Render();
	}
}
void TileMap::Clear()
{
	for (auto it = tileMap.begin(); it != tileMap.end(); it++)
	{
		delete (*it);
	}
	tileMap.clear();
}