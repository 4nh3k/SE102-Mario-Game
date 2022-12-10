#include <iostream>
#include <fstream>
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
#include "Koopa.h"
#include "SampleKeyEventHandler.h"

using namespace std;

PlayScene::PlayScene(int id, LPCWSTR filePath):
	Scene(id, filePath)
{
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

void PlayScene::LoadObjectAni(int objectType)
{
	LPANIMATION ani = new Animation();
	LPTEXTURE tex = Textures::GetInstance()->Get("20");
	switch (objectType)
	{
	case OBJECT_TYPE_MARIO:
		Animations::GetInstance()->LoadAnimation(ANIMATIONS_PATH_MARIO);
		break;
	case OBJECT_TYPE_BRICK:
		Sprites::GetInstance()->Add("20001", 372, 153, 387, 168, tex);
		ani->Add("20001", 1000);
		Animations::GetInstance()->Add("10000", ani);
		break;
	case OBJECT_TYPE_QUESTION_BLOCK:
		Animations::GetInstance()->LoadAnimation(ANIMATIONS_PATH_QUESTION_BLOCK);
	case OBJECT_TYPE_ENEMIES:
		Animations::GetInstance()->LoadAnimation(ANIMATIONS_PATH_ENEMIES);
		break;
	default:
		break;
	}
}


void PlayScene::LoadObjects(vector<tson::Object> objects)
{
	for (auto& obj : objects)
	{
		LPGAMEOBJECT gameObj = NULL;
		tson::Vector2i pos = obj.getPosition();
		if (obj.getName() == "Platform")
		{
			tson::Vector2i size = obj.getSize();
			gameObj = new Platform
			(
				pos.x + size.x / 2, pos.y + size.y / 2,
				size.x, size.y
			);
		}
		if (obj.getName() == "Special_Platform")
		{
			tson::Vector2i size = obj.getSize();
			gameObj = new SpecialPlatform
			(
				pos.x + size.x / 2, pos.y + size.y / 2,
				size.x, size.y
			);
		}
		if (obj.getName() == "Koopa")
		{
			gameObj = new Koopa(pos.x, pos.y);
		}
		if (obj.getName() == "Mario")
		{
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				return;
			}
			gameObj = new Mario(pos.x +10, pos.y+10);
			player = (Mario*)gameObj;

			DebugOut(L"[INFO] Player object has been created!\n");
		}
		if (obj.getName() == "Brick")
		{
			gameObj = new Brick(pos.x, pos.y);
		}
		if (obj.getName() == "Question Block")
		{
			tson::Property* prop = obj.getProp("reward_id");
			int reward_id = any_cast<int>(prop->getValue());
			// calculate in-game x, y because this object is represented by a point in tiled map
			int x = ((pos.x / 16) * 16 + 8);
			int y = ((pos.y / 16) * 16 + 8);
			LPGAMEOBJECT reward = QuestionBlock::GetReward(reward_id, x, y);
			gameObjects.push_back(reward);
			gameObj = new QuestionBlock(x, y, reward);
		}
		if (obj.getName() == "Portal")
		{
			tson::Vector2i size = obj.getSize();
			tson::Property* prop = obj.getProp("scene_id");
			int scene_id = any_cast<int>(prop->getValue());
			gameObj = new Portal(pos.x, pos.y, size.x + pos.x, pos.y + size.y,scene_id);
		}
		if (obj.getName() == "Goomba")
		{
			gameObj = new Goomba(pos.x, pos.y);
		}
		//gameObj->SetPosition(10.0f, 01.0f);
		gameObjects.push_back(gameObj);
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
			if (layer.getType() == tson::LayerType::ObjectGroup)
			{
				tson::Property* prop = layer.getProp("object_type");
				int object_type = any_cast<int>(prop->getValue());
				LoadObjectAni(object_type);
				LoadObjects(layer.getObjects());
			}
			if (layer.getType() == tson::LayerType::TileLayer)
			{
				if (!map->isInfinite())
				{
					tson::Vector2i tileSize = map->getTileSize();
					for (auto& [pos, tileObject] : layer.getTileObjects())
					{
						tson::Vector2f position = tileObject.getPosition();
						string tileId = to_string(tileObject.getTile()->getGid());
						// position + tileSize/2 because the difference between tiled map x, y and this game x,y
						Tile* tile = new Tile(position.x + tileSize.x / 2, position.y + tileSize.y / 2,
							tileSize.x,tileSize.y, tileId);
						tileMap.push_back(tile);
					}
				}
			}

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
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		if(!dynamic_cast<Mario*>(gameObjects[i]))
			coObjects.push_back(gameObjects[i]);
	}

	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		//only update object when it inside camera
		float l,t,r,b;
		RECT rect;
		gameObjects[i]->GetBoundingBox(l, t, r, b);
		rect.left = l; rect.top = t; rect.right = r; rect.bottom = b;
		if (Game::GetInstance()->GetCamera()->IsContain(rect))
			gameObjects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	Game *game = Game::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;

	if (cx < 0) cx = 0;

	Game::GetInstance()->GetCamera()->SetCamPos(cx, camY);

	PurgeDeletedObjects();
}

void PlayScene::Render()
{
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
}

/*
*	Clear all objects from this scene
*/
void PlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); it++)
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
	vector<LPGAMEOBJECT>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); it++)
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
	gameObjects.erase(
		std::remove_if(gameObjects.begin(), gameObjects.end(), PlayScene::IsGameObjectDeleted),
		gameObjects.end());
}