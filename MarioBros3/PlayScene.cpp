#include <iostream>
#include <fstream>
#include "Mario.h"
#include "Brick.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "SpecialPlatform.h"
#include "QuestionBlock.h"
#include "RewardCoin.h"
#include "Koopa.h"
#include "Goomba.h"
#include "RedKoopa.h"
#include "VenusFireTrap.h"
#include "SampleKeyEventHandler.h"

using namespace std;

PlayScene::PlayScene(int id, LPCWSTR filePath):
	Scene(id, filePath)
{
	camY = 0.0f;
	player = NULL;
	key_handler = new SampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1

void PlayScene::LoadTilesets(vector<tson::Tileset> tileSets)
{
	for (auto& tileSet : tileSets)
	{
		string image = tileSet.getImagePath().u8string();

		filesystem::path path = sceneFilePath;
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

void PlayScene::LoadObjects(vector<tson::Object> objects)
{
	for (auto& obj : objects)
	{
		LPGAMEOBJECT gameObj = NULL;

		tson::Vector2f pos = ToInGamePos(obj);
		tson::Vector2i size = obj.getSize();

		if (obj.getName() == "Platform")
		{
			gameObj = new Platform(pos.x, pos.y, size.x, size.y);
		}
		else if (obj.getName() == "Special_Platform")
		{
			gameObj = new SpecialPlatform(pos.x, pos.y, size.x, size.y);
		}
		else if (obj.getName() == "Koopa")
		{
			gameObj = new Koopa(pos.x, pos.y);
		}
		else if (obj.getName() == "RedKoopa")
		{
			gameObj = new RedKoopa(pos.x, pos.y);
		}
		else if (obj.getName() == "Mario")
		{
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				continue;
			}
			gameObj = new Mario(pos.x, pos.y);
			player = (Mario*)gameObj;
			DebugOut(L"[INFO] Player object has been created!\n");
			continue;
		}
		else if (obj.getName() == "Brick")
		{
			gameObj = new Brick(pos.x, pos.y);
		}
		else if (obj.getName() == "Question Block")
		{
			int reward_id = GetProperty(obj, PROP_ID_REWARD);
			QuestionBlock* qblock = new QuestionBlock(pos.x, pos.y, reward_id);
			gameObj = qblock;
		}
		else if (obj.getName() == "Portal")
		{
			int scene_id = GetProperty(obj, PROP_ID_SCENE);
			gameObj = new Portal(pos.x, pos.y, size.x + pos.x, pos.y + size.y,scene_id);
		}
		else if (obj.getName() == "Goomba")
		{
			gameObj = new Goomba(pos.x, pos.y);
		}
		else if (obj.getName() == "Coin")
		{
			gameObj = new Coin(pos.x, pos.y);
		}
		else if (obj.getName() == "Venus")
		{
			gameObj = new VenusFireTrap(pos.x, pos.y);
			lowLayer.push_back(gameObj);
			continue;
		}
		//gameObj->SetPosition(10.0f, 01.0f);
		gameObjects.push_back(gameObj);
	}
}

void PlayScene::LoadTileObjects(map<tuple<int, int>, tson::TileObject> tileObjects, tson::Vector2i tileSize)
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

void PlayScene::LoadLayer(tson::Layer layer, tson::Vector2i tileSize)
{
	string aniPath;
	switch (layer.getType())
	{
	case tson::LayerType::Group:
		aniPath = GetProperty(layer, PROP_ID_ANI_PATH);
		if (!aniPath.empty())
			Animations::GetInstance()->LoadAnimation(aniPath);
		for (auto& objLayer : layer.getLayers())
		{
			LoadLayer(objLayer, tileSize);
		}
		break;
	case tson::LayerType::TileLayer:
		LoadTileObjects(layer.getTileObjects(), tileSize);
		break;
	case tson::LayerType::ObjectGroup:
		LoadObjects(layer.getObjects());
		break;
	default:
		break;
	}
}

void PlayScene::Load()
{
	DebugOutTitle(L"Start load");

	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	unique_ptr<tson::Map> map;
	tson::Tileson t;
	map = t.parse(fs::path(sceneFilePath));

	camY = any_cast<int>(map->getProp("cam_y")->getValue());
	camY -= Game::GetInstance()->GetBackBufferHeight();

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		DebugOut(L"[INFO] Load map successfully from file: %s \n", sceneFilePath);
		LoadTilesets(map->getTilesets());

		for (auto& layer : map->getLayers())
		{
			LoadLayer(layer, map->getTileSize());
		}
		DebugOutTitle(L"Done load");

	}
	else
	{
		DebugOut(L"[ERROR] Load map failed from file: %s", sceneFilePath);

	}

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}


void PlayScene::Update(DWORD dt)
{
	if (this->IsPause()) 
		return;
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (auto& obj : lowLayer)
	{
		coObjects.push_back(obj);
	}
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		//if(dynamic_cast<Mario*>(gameObjects[i]))
		coObjects.push_back(gameObjects[i]);
	}
	for (auto& obj : lowLayer)
	{
		obj->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 
	else
	{
		player->Update(dt, &coObjects);
	}
	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	Mario* mario = dynamic_cast<Mario*>(player);

	Game *game = Game::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;


	if (cx < 0) cx = 0;
	// move camY follow mario when flying up
	if (cy > camY - game->GetBackBufferHeight()/8 || !mario->IsTanooki())
	{
		cy = camY;
	}
	else
	{
		cy += game->GetBackBufferHeight() / 8;
	}
	Game::GetInstance()->GetCamera()->SetCamPos(cx, cy);

	PurgeDeletedObjects();
}

void PlayScene::Render()
{
	//if (this->IsPause()) 
	//	return;
	for (auto& obj : lowLayer)
	{
		obj->Render();
	}
	// Draw background first
	for (auto& tile : tileMap)
	{
		RECT rect;
		tile->GetBoundingBox(rect.left, rect.top, rect.right, rect.bottom);
		if(Game::GetInstance()->GetCamera()->IsContain(rect))
			tile->Render();
	}
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Render();
	if (player != NULL) 
		player->Render();
}
/*
*	Clear all objects from this scene
*/
void PlayScene::Clear()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		delete (*it);
	}
	gameObjects.clear();
	tileMap.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void PlayScene::Unload()
{
	for (int i = 0; i < gameObjects.size(); i++)
		delete gameObjects[i];

	gameObjects.clear();

	//Sprites::GetInstance()->Clear();
	//Animations::GetInstance()->Clear();
	//Textures::GetInstance()->Clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool PlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void PlayScene::PurgeDeletedObjects()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	for (auto it = lowLayer.begin(); it != lowLayer.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	lowLayer.erase(
		std::remove_if(lowLayer.begin(), lowLayer.end(), PlayScene::IsGameObjectDeleted),
		lowLayer.end());

	gameObjects.erase(
		std::remove_if(gameObjects.begin(), gameObjects.end(), PlayScene::IsGameObjectDeleted),
		gameObjects.end());
}