#include "Map.h"

Map::Map(string mapPath)
{
	Load(mapPath);
}
void Map::Load(string mapPath)
{
	unique_ptr<tson::Map> map;
	tson::Tileson t;
	map = t.parse(fs::path(mapPath));
	if (map->getStatus() == tson::ParseStatus::OK)
	{
		DebugOut(L"[INFO] Load map successfully from file: %s", mapPath);
		for (auto& tileSet : map->getTilesets())
		{
			string image = tileSet.getImagePath().u8string();
			Textures::GetInstance()->Add(100, ToLPCWSTR("./textures/Map/" + image));
			for (auto& tile : tileSet.getTiles())
			{
				tson::Rect drawingRect = tile.getDrawingRect();
				Sprites::GetInstance()->Add(
					to_string(tile.getGid()),
					drawingRect.x, drawingRect.y,
					drawingRect.x + drawingRect.height, drawingRect.y + drawingRect.width,
					Textures::GetInstance()->Get(100)
				);
			}
		}
		for (auto& layer : map->getLayers())
		{
			//For tile flayers, you can get the tiles presented as a 2D map by calling getTileData()
			//Using x and y positions in tile units.
			if (layer.getType() == tson::LayerType::TileLayer)
			{
				//When the map is of a fixed size, you can get the tiles like this
				if (!map->isInfinite())
				{
					for (auto& [pos, tileObject] : layer.getTileObjects()) //Loops through absolutely all existing tileObjects
					{
						tson::Vector2f position = tileObject.getPosition();
						drawPos.push_back({ to_string(tileObject.getTile()->getGid()), {position.x + 10, position.y + 10} });
 					}
				}
			}

		}
	}
	else
	{
		DebugOut(L"[ERROR] Load map failed from file: %s", mapPath);

	}
}
void Map::Render()
{
	for (auto& a : drawPos)
	{
		Sprites::GetInstance()->Get(a.first)->Draw(a.second.first, a.second.second);
	}
}

