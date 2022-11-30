#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "tileson.hpp"
//#include "Koopas.h"


class PlayScene: public Scene
{
protected: 
	vector<pair<string, pair<float, float>>> drawPos;

	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					
	vector<LPGAMEOBJECT> gameObjects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void LoadObjects(vector < tson::Object> objects);
	void LoadTilesets(vector<tson::Tileset> tileSets);
	void LoadAssets(LPCWSTR assetFile);
	
public: 
	PlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef PlayScene* LPPLAYSCENE;

