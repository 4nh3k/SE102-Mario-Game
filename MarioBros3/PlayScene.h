#pragma once
#include "Game.h"
#include "Scene.h"
#include "tileson.hpp"

#define SCENE_SECTION_UNKNOWN -1

class PlayScene: public Scene
{
protected: 
	float preCamY;
	vector<std::pair<tson::Object, bool>> spawnPoint;
	LPGAMEOBJECT hud;

	void LoadObjects(vector < tson::Object> objects);
	void LoadLayer(tson::Layer layer, tson::Vector2i tileSize);
	void Spawn(tson::Object);
	
public: 
	PlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual int GetBackGroundColor() { return BLUE_BACKGROUND_ID; }

	void Clear();
	void PurgeDeletedObjects(std::deque<LPGAMEOBJECT> &list);
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef PlayScene* LPPLAYSCENE;

