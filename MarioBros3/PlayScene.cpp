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

#include "SampleKeyEventHandler.h"

using namespace std;

PlayScene::PlayScene(int id, LPCWSTR filePath):
	Scene(id, filePath)
{
	player = NULL;
	key_handler = new SampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void PlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	string ID = tokens[0].c_str();
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = Textures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	Sprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void PlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	if (path == ToWSTR("mario.txt"))
	{
		Animations::GetInstance()->LoadAnimation(ANIMATIONS_PATH_MARIO);
	}
	else
	{
		LoadAssets(path.c_str());
	}
}

void PlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new Animation();

	string ani_id = tokens[0].c_str();
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		string sprite_id = tokens[i].c_str();
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	Animations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void PlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	GameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new Mario(x,y); 
		player = (Mario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new Goomba(x,y); break;
	case OBJECT_TYPE_BRICK: obj = new Brick(x,y); break;
	case OBJECT_TYPE_COIN: obj = new Coin(x, y); break;

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		string sprite_begin = (tokens[6].c_str());
		string sprite_middle = (tokens[7].c_str());
		string sprite_end = (tokens[8].c_str());

		obj = new Platform(
			x, y,
			cell_width, cell_height
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new Portal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	gameObjects.push_back(obj);
}


void PlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}
void PlayScene::LoadTilesets(vector<tson::Tileset> tileSets)
{
	for (auto& tileSet : tileSets)
	{
		string image = tileSet.getImagePath().u8string();
		Textures::GetInstance()->Add(100, ToLPCWSTR("./textures/Map/" + image));

		for (auto& tile : tileSet.getTiles())
		{
			tson::Rect drawingRect = tile.getDrawingRect();
			Sprites::GetInstance()->Add(
				to_string(tile.getGid()),
				drawingRect.x, drawingRect.y,
				drawingRect.x + drawingRect.width, drawingRect.y + drawingRect.height,
				Textures::GetInstance()->Get(100)
			);
		}
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
				pos.x+size.x/2, pos.y+size.y/2,
				size.x, size.y
			);
		}
		if (obj.getName() == "Mario")
		{
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				return;
			}
			Animations::GetInstance()->LoadAnimation(ANIMATIONS_PATH_MARIO);
			gameObj = new Mario(pos.x +10, pos.y+10);
			player = (Mario*)gameObj;

			DebugOut(L"[INFO] Player object has been created!\n");
		}
		if (obj.getName() == "Brick")
		{
			//20001	372	153	387	168	20
			//10000	20001	1000
			LPANIMATION ani = new Animation();
			LPTEXTURE tex = Textures::GetInstance()->Get(20);
			Sprites::GetInstance()->Add("20001", 372, 153, 387, 168,tex);
			ani->Add("20001", 1000);
			Animations::GetInstance()->Add("10000", ani);

			gameObj = new Brick(pos.x, pos.y);
		}
		//gameObj->SetPosition(10.0f, 01.0f);
		gameObjects.push_back(gameObj);
	}
}
void PlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);
	unique_ptr<tson::Map> map;
	tson::Tileson t;
	map = t.parse(fs::path(sceneFilePath));
	if (map->getStatus() == tson::ParseStatus::OK)
	{
		DebugOut(L"[INFO] Load map successfully from file: %s", sceneFilePath);
		LoadTilesets(map->getTilesets());
		for (auto& layer : map->getLayers())
		{
			if (layer.getType() == tson::LayerType::ObjectGroup)
			{
				LoadObjects(layer.getObjects());
			}
			//For tile flayers, you can get the tiles presented as a 2D map by calling getTileData()
			//Using x and y positions in tile units.
			if (layer.getType() == tson::LayerType::TileLayer)
			{
				//When the map is of a fixed size, you can get the tiles like this
				if (!map->isInfinite())
				{
					tson::Vector2i tileSize = map->getTileSize();
					for (auto& [pos, tileObject] : layer.getTileObjects()) //Loops through absolutely all existing tileObjects
					{
						tson::Vector2f position = tileObject.getPosition();
						drawPos.push_back({ to_string(tileObject.getTile()->getGid()), 
							{position.x + tileSize.x/2 , position.y + tileSize.y/2} });
					}
				}
			}

		}
	}
	else
	{
		DebugOut(L"[ERROR] Load map failed from file: %s", sceneFilePath);

	}
	/*
	* 	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();
	*/


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
		gameObjects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	Game *game = Game::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;

	//CGame::GetInstance()->SetCamPos(cx, 200.0f);

	PurgeDeletedObjects();
}

void PlayScene::Render()
{
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Render();
	for (auto& tile : drawPos)
	{
		Sprites::GetInstance()->Get(tile.first)->Draw(tile.second.first, tile.second.second);
	}
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
	drawPos.clear();
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