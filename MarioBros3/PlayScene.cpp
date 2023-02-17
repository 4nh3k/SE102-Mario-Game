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
#include "RewardBrick.h"
#include "PlaySceneKeyHandler.h"
#include "ParaGoomba.h"
#include "GreenVenus.h"
#include "PiranhaPlant.h"
#include "ParaKoopa.h"
#include "Pipeline.h"
#include "TheVoid.h"
#include "MarioMap.h"
#include "HUD.h"
#include "TileMap.h"
#include "Goal.h"

using namespace std;

PlayScene::PlayScene(int id, LPCWSTR filePath):
	Scene(id, filePath)
{
	camY = 0.0f;
	player = NULL;
	key_handler = new PlaySceneKeyHandler(this);
	tileMap = new TileMap();
}

bool PlayScene::CanControl()
{
	Mario* mario = dynamic_cast<Mario*>(player);
	return (!mario->HasFinish());
}

void PlayScene::Spawn(tson::Object obj)
{
	LPGAMEOBJECT gameObj = NULL;

	tson::Vector2f pos = ToInGamePos(obj);
	tson::Vector2i size = obj.getSize();
	if (obj.getName() == "Koopa")
	{
		gameObj = new Koopa(pos.x, pos.y);
	}
	else if (obj.getName() == "RedKoopa")
	{
		gameObj = new RedKoopa(pos.x, pos.y);
	}
	else if (obj.getName() == "ParaKoopa")
	{
		gameObj = new ParaKoopa(pos.x, pos.y);
	}
	else if (obj.getName() == "Goomba")
	{
		gameObj = new Goomba(pos.x, pos.y);
	}
	else if (obj.getName() == "Venus")
	{
		gameObj = new VenusFireTrap(pos.x, pos.y);
		lowLayer.push_back(gameObj);
		return;
	}
	else if (obj.getName() == "GreenVenus")
	{
		gameObj = new GreenVenus(pos.x, pos.y);
		lowLayer.push_back(gameObj);
		return;
	}
	else if (obj.getName() == "PiranhaPlant")
	{
		gameObj = new PiranhaPlant(pos.x, pos.y);
		lowLayer.push_back(gameObj);
		return;
	}
	else if (obj.getName() == "ParaGoomba")
	{
		gameObj = new ParaGoomba(pos.x, pos.y);
	}
	//gameObj->SetPosition(10.0f, 01.0f);
	gameObjects.push_back(gameObj);
}

void PlayScene::LoadObjects(vector<tson::Object> objects)
{
	for (auto& obj : objects)
	{
		LPGAMEOBJECT gameObj = NULL;
		tson::Object spawnObj = obj;

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
			gameObj = new QuestionBlock(pos.x, pos.y, reward_id);;
		}
		else if (obj.getName() == "Portal")
		{
			int scene_id = GetProperty(obj, PROP_ID_SCENE);
			gameObj = new Portal(pos.x, pos.y, size.x + pos.x, pos.y + size.y,scene_id);
		}
		else if (obj.getName() == "Goal")
		{
			gameObj = new Goal(pos.x, pos.y, size.x, size.y);
		}
		else if (obj.getName() == "Coin")
		{
			gameObj = new Coin(pos.x, pos.y);
		}
		else if (obj.getName() == "Reward Brick")
		{
			int reward_id = GetProperty(obj, PROP_ID_REWARD);
			gameObj = new RewardBrick(pos.x, pos.y, reward_id);
		}
		else if (obj.getName() == "Pipeline")
		{
			int targetX = GetProperty(obj, "x");
			int targetY = GetProperty(obj, "y");
			int tmp = GetProperty(obj, "camY");
			tmp -= Game::GetInstance()->GetBackBufferHeight();
			gameObj = new Pipeline(pos.x, pos.y, size.x, size.y, targetX, targetY,camX,tmp);
		}
		else if (obj.getName() == "TheVoid")
		{
			gameObj = new TheVoid(pos.x, pos.y, size.x, size.y);
		}
		else {
			spawnPoint.push_back({ obj, false });
			continue;
		}
		//gameObj->SetPosition(10.0f, 01.0f);
		gameObjects.push_back(gameObj);
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
		tileMap->LoadTileObjects(layer.getTileObjects(), tileSize);
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

	hud = HUD::GetInstance();
	SFXs.push_back(hud);

	HUD::GetInstance()->StartTimer();

	unique_ptr<tson::Map> map;
	tson::Tileson t;
	map = t.parse(fs::path(sceneFilePath));

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		if (map->getProperties().hasProperty("cam_y"))
		{
			camY = any_cast<int>(map->getProp("cam_y")->getValue());
			camY -= Game::GetInstance()->GetBackBufferHeight();
		}
		if (map->getProperties().hasProperty("cam_x"))
		{
			camX = any_cast<int>(map->getProp("cam_x")->getValue());
			camX -= Game::GetInstance()->GetBackBufferWidth();
		}
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


void PlayScene::Update(DWORD dt)
{

	for (auto& obj : spawnPoint)
	{
		tson::Vector2i pos = obj.first.getPosition();
		bool isContain = Game::GetInstance()->GetCamera()->IsContain(pos.x, pos.y);
		//DebugOutTitle(L"%d, %d",pos.x, pos.y);
		if (isContain && !obj.second)
		{
			obj.second = true;
			DebugOutTitle(L"%d, %d", pos.x, pos.y);
			Spawn(obj.first);
		}
	}
	vector<LPGAMEOBJECT> coObjects;
	if (this->IsPause())
		return;
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	for (auto& obj : lowLayer)
	{
		coObjects.push_back(obj);
	}
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		//if(dynamic_cast<Mario*>(gameObjects[i]))
		coObjects.push_back(gameObjects[i]);
	}
	if (player != NULL)
	{
		player->Update(dt, &coObjects);
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
	if (SFXs.size() > 0)
	{
		for (auto& sfx : SFXs)
		{
			sfx->Update(dt, &coObjects);
		}

	}
	for (auto& obj : lowLayer)
	{
		obj->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update(dt, &coObjects);
	}

	if (HUD::GetInstance()->HasFinishScene())
	{
		Game* game = Game::GetInstance();
		int level = dynamic_cast<Mario*>(player)->GetLevel();
		game->InitiateSwitchScene(WORLD_MAP_ID);
		game->SwitchScene();
		MarioMap* mario = dynamic_cast<MarioMap*>(game->GetCurrentScene()->GetPlayer());
		mario->GetCurrentNode()->SetClear(true);
		mario->SetLevel(level);
		HUD::GetInstance()->ResetTimer();
		HUD::GetInstance()->SetHasFinishScene();
		return;
	}

	// Update camera to follow mario
	float cx, cy;
	float py;
	player->GetPosition(cx, cy);
	Mario* mario = dynamic_cast<Mario*>(player);
	Game* game = Game::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;
	py = cy;


	if (cx < 0) cx = 0;
	// move camY follow mario when flying up
	if (cy > camY - game->GetBackBufferHeight() / 8 || !mario->IsTanooki())
	{
		cy = camY;
	}
	else
	{
		cy += game->GetBackBufferHeight() / 8;

	}

	if (cx < camX)
	{
		hud->SetPosition(cx + HUD_WIDTH / 2, cy + HUD_HEIGHT / 2 + game->GetBackBufferHeight());
		preCamY = cy;
		Game::GetInstance()->GetCamera()->SetCamPos(cx , cy + HUD_HEIGHT);
	}

	PurgeDeletedObjects();
}

void PlayScene::Render()
{
	//if (this->IsPause()) 
	//	return;
	bool teleporting = dynamic_cast<Mario*>(player)->IsGoingPipeLine();
	if ((player != NULL) && teleporting)
	{
		player->Render();
	}
	for (auto& obj : lowLayer)
	{
		obj->Render();
	}
	// Draw background first
	tileMap->Render();
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Render();
	if (player != NULL && !teleporting) 
		player->Render();
	for (auto& sfx : SFXs)
	{
		sfx->Render();
	}
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
	for (auto it = lowLayer.begin(); it != lowLayer.end(); it++)
	{
		delete (*it);
	}
	SFXs.clear();
	spawnPoint.clear();
	gameObjects.clear();
	lowLayer.clear();
	tileMap->Clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void PlayScene::Unload()
{
	Clear();

	//Sprites::GetInstance()->Clear();
	//Animations::GetInstance()->Clear();
	//Textures::GetInstance()->Clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool PlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void PlayScene::PurgeDeletedObjects(std::deque<LPGAMEOBJECT> &list)
{
	for (auto it = list.begin(); it != list.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	list.erase(
		std::remove_if(list.begin(), list.end(), PlayScene::IsGameObjectDeleted),
		list.end());
}

void PlayScene::PurgeDeletedObjects()
{
	PurgeDeletedObjects(gameObjects);
	PurgeDeletedObjects(lowLayer);
	PurgeDeletedObjects(SFXs);
	//for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	//{
	//	LPGAMEOBJECT o = *it;
	//	if (o->IsDeleted())
	//	{
	//		delete o;
	//		*it = NULL;
	//	}
	//}
	//for (auto it = lowLayer.begin(); it != lowLayer.end(); it++)
	//{
	//	LPGAMEOBJECT o = *it;
	//	if (o->IsDeleted())
	//	{
	//		delete o;
	//		*it = NULL;
	//	}
	//}
	//for (auto it = SFXs.begin(); it != SFXs.end(); it++)
	//{
	//	LPGAMEOBJECT o = *it;
	//	if (o->IsDeleted())
	//	{
	//		delete o;
	//		*it = NULL;
	//	}
	//}	// NOTE: remove_if will swap all deleted items to the end of the vector
	//// then simply trim the vector, this is much more efficient than deleting individual items
	//lowLayer.erase(
	//	std::remove_if(lowLayer.begin(), lowLayer.end(), PlayScene::IsGameObjectDeleted),
	//	lowLayer.end());

	//gameObjects.erase(
	//	std::remove_if(gameObjects.begin(), gameObjects.end(), PlayScene::IsGameObjectDeleted),
	//	gameObjects.end());
}