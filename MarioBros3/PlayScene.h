#pragma once
#include "Game.h"
#include "Scene.h"
#include "tileson.hpp"
#include "EnemyObjFactory.h"
#include "PlatformObjFactory.h"

#define SCENE_SECTION_UNKNOWN -1

class PlayScene: public Scene
{
protected: 
	int backgroundColor;
	float preCamY;
	bool startMoving;
	vector<std::pair<tson::Object, bool>> spawnPoint;
	LPGAMEOBJECT hud;
	GameObjFactory* enemyFactory;
	GameObjFactory* platformFactory;

	void LoadObjects(vector < tson::Object> objects);
	void LoadLayer(tson::Layer layer, tson::Vector2i tileSize);
	void Spawn(tson::Object);
	
public: 
	PlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual int GetBackGroundColor() { return backgroundColor; }
	virtual void SetBackGroundColor(int colorId) {
		backgroundColor = colorId;
	}

	void Clear();
	void PurgeDeletedObjects(std::deque<LPGAMEOBJECT> &list);
	void PurgeDeletedObjects();

	bool CanControl();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef PlayScene* LPPLAYSCENE;

