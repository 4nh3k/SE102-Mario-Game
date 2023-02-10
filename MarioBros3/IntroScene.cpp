#include "IntroScene.h"
#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "IntroSceneKeyHandler.h"
#include "TileMap.h"

#define START_NODE_ID 1

using namespace std;

IntroScene::IntroScene(int id, LPCWSTR filePath) :
	Scene(id, filePath)
{
	camY = 0.0f;
	player = NULL;
	key_handler = new IntroSceneKeyHandler(this);
	cursorY = CURSOR_POS_Y_1;
	tileMap = new TileMap();
}

void IntroScene::LoadObjects(vector<tson::Object> objects)
{
	for (auto& obj : objects)
	{
		LPGAMEOBJECT gameObj = NULL;
		tson::Object spawnObj = obj;

		tson::Vector2f pos = ToInGamePos(obj);
		tson::Vector2i size = obj.getSize();

		if (obj.getName() == "Mario")
		{
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				continue;
			}
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

			continue;
		}
		gameObjects.push_back(gameObj);
	}
}

void IntroScene::LoadLayer(tson::Layer layer, tson::Vector2i tileSize)
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

void IntroScene::Load()
{
	DebugOutTitle(L"Start load");

	Game::GetInstance()->GetCamera()->SetCamPos(5, 0);
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	unique_ptr<tson::Map> map;
	tson::Tileson t;
	map = t.parse(fs::path(sceneFilePath));

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		DebugOut(L"[INFO] Load map successfully from file: %s \n", sceneFilePath);
		tileMap->LoadTilesets(sceneFilePath,map->getTilesets());

		for (auto& layer : map->getLayers())
		{
			LoadLayer(layer, map->getTileSize());
		}
		//DebugOutTitle(L"Done load");
		DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);

	}
	else
	{
		DebugOut(L"[ERROR] Load map failed from file: %s", sceneFilePath);

	}

}


void IntroScene::Update(DWORD dt)
{
	if (this->IsPause())
		return;
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
	else
	{
		player->Update(dt);
	}
	PurgeDeletedObjects();
}

void IntroScene::Render()
{
	// Draw background first
	tileMap->Render();
	Animations::GetInstance()->Get(ID_ANI_NUMBER3)->Render(NUMBER3_POS_X, NUMBER3_POS_Y);
	Animations::GetInstance()->Get(ID_ANI_CURSOR)->Render(CURSOR_POS_X, cursorY);
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Render();
	for (auto& sfx : SFXs)
	{
		sfx->Render();
	}
}
void IntroScene::MoveCursor()
{
	cursorY = (cursorY == CURSOR_POS_Y_1) ? CURSOR_POS_Y_2 : CURSOR_POS_Y_1;
}
/*
*	Clear all objects from this scene
*/
void IntroScene::Clear()
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
void IntroScene::Unload()
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

bool IntroScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void IntroScene::PurgeDeletedObjects(std::deque<LPGAMEOBJECT>& list)
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
		std::remove_if(list.begin(), list.end(), IntroScene::IsGameObjectDeleted),
		list.end());
}

void IntroScene::PurgeDeletedObjects()
{
	PurgeDeletedObjects(gameObjects);
	PurgeDeletedObjects(lowLayer);
	PurgeDeletedObjects(SFXs);
}