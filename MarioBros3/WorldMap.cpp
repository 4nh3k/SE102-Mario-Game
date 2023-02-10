#include "WorldMap.h"
#include <iostream>
#include <fstream>
#include "MarioMap.h"
#include "AssetIDs.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "MapSceneKeyHandler.h"
#include "MapBush.h"
#include "HUD.h"
#include "TileMap.h"

#define START_NODE_ID 1

using namespace std;

WorldMap::WorldMap(int id, LPCWSTR filePath) :
	Scene(id, filePath)
{
	camY = 0.0f;
	player = NULL;
	key_handler = new MapSceneKeyHandler(this);
	hud = HUD::GetInstance();
	SFXs.push_back(hud);
	tileMap = new TileMap();
}

void WorldMap::LoadObjects(vector<tson::Object> objects)
{
	for (auto& obj : objects)
	{
		LPGAMEOBJECT gameObj = NULL;
		tson::Object spawnObj = obj;

		tson::Vector2f pos = ToInGamePos(obj);
		tson::Vector2i size = obj.getSize();

		if (obj.getName() == "Bush")
		{
			gameObj = new MapBush(pos.x, pos.y);
		}
		else if (obj.getName() == "Mario")
		{
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				continue;
			}
			gameObj = new MarioMap(pos.x, pos.y);
			player = (MarioMap*)gameObj;
			DebugOut(L"[INFO] Player object has been created!\n");
			continue;
		}
		else if (obj.getName() == "Node")
		{
			int id = GetProperty(obj, "id");
			int left = GetProperty(obj, "left");
			int right = GetProperty(obj, "right");
			int top = GetProperty(obj, "top");
			int bot = GetProperty(obj, "bot");
			int scene_id = GetProperty(obj, "scene_id");

			MapNode* node = new MapNode(id, pos.x, pos.y,left,right,top,bot,scene_id);
			movingMap[id] = node;
			continue;
		}
		gameObjects.push_back(gameObj);
	}
}

void WorldMap::LoadLayer(tson::Layer layer, tson::Vector2i tileSize)
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
		tileMap->LoadTileObjects(layer.getTileObjects(), tileSize);
		break;
	case tson::LayerType::ObjectGroup:
		LoadObjects(layer.getObjects());
		break;
	default:
		break;
	}
}
void WorldMap::InitMap()
{
	for (auto node : movingMap)
	{
		int l, r, b, t;
		node.second->GetNextNode(l,r,t,b);
		if (movingMap.find(l) != movingMap.end())
		{
			node.second->Left = movingMap[l];
		}
		if (movingMap.find(r) != movingMap.end())
		{
			node.second->Right = movingMap[r];
		}
		if (movingMap.find(t) != movingMap.end())
		{
			node.second->Top = movingMap[t];
		}
		if (movingMap.find(b) != movingMap.end())
		{
			node.second->Bot = movingMap[b];
		}
	}
	dynamic_cast<MarioMap*>(player)->SetCurrentNode(movingMap[START_NODE_ID]);
}

void WorldMap::Load()
{
	DebugOutTitle(L"Start load");

	Game::GetInstance()->GetCamera()->SetCamPos(5, 0);
	hud->SetPosition(HUD_POS_X, HUD_POS_Y);
	MomentumBar::GetInstance()->SetNode(0);
	hud->ResetTimer();
	hud->StopTimer();
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	unique_ptr<tson::Map> map;
	tson::Tileson t;
	map = t.parse(fs::path(sceneFilePath));

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		DebugOut(L"[INFO] Load map successfully from file: %s \n", sceneFilePath);
		tileMap->LoadTilesets(sceneFilePath, map->getTilesets());

		for (auto& layer : map->getLayers())
		{
			LoadLayer(layer, map->getTileSize());
		}
		InitMap();
		//DebugOutTitle(L"Done load");
		DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);

	}
	else
	{
		DebugOut(L"[ERROR] Load map failed from file: %s", sceneFilePath);

	}

}


void WorldMap::Update(DWORD dt)
{
	if (this->IsPause())
		return;
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
	else
	{
		player->Update(dt);
	}
	HUD::GetInstance()->Update(dt,NULL);
	PurgeDeletedObjects();
}

void WorldMap::Render()
{
	// Draw background first
	tileMap->Render();
	for (auto node : movingMap)
	{
		node.second->Render();
	}
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Render();
	if (player != NULL)
		player->Render();
	for (auto& sfx : SFXs)
	{
		sfx->Render();
	}
}
/*
*	Clear all objects from this scene
*/
void WorldMap::Clear()
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		delete (*it);
	}
	gameObjects.clear();
	tileMap->Clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void WorldMap::Unload()
{
	for (int i = 0; i < gameObjects.size(); i++)
		delete gameObjects[i];

	gameObjects.clear();

	//Sprites::GetInstance()->Clear();
	//Animations::GetInstance()->Clear();
	//Textures::GetInstance()->Clear();
	// // keep mario map?
	//player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool WorldMap::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void WorldMap::PurgeDeletedObjects(std::deque<LPGAMEOBJECT>& list)
{
	for (auto it = list.begin(); it != list.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	list.erase(
		std::remove_if(list.begin(), list.end(), WorldMap::IsGameObjectDeleted),
		list.end());
}

void WorldMap::PurgeDeletedObjects()
{
	PurgeDeletedObjects(gameObjects);
	PurgeDeletedObjects(lowLayer);
	PurgeDeletedObjects(SFXs);
}