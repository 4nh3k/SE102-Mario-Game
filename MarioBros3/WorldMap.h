#pragma once
#include "Game.h"
#include "Scene.h"
#include "tileson.hpp"
#include "Tile.h"
#include "MapNode.h"
#include "HUD.h"
#include "MapObjFactory.h"

#define HUD_HEIGHT 36
#define HUD_POS_Y (176 + HUD_HEIGHT/2)
#define HUD_POS_X (16*8)
#define POPUP_OFFSET_X 10
#define POPUP_OFFSET_Y (HUD_HEIGHT)
#define ID_ANI_CURSOR	"cursor"
#define CURSOR_POS_X_OFFSET 8
#define CURSOR_POS_Y 93
#define CONTINUTE_ID 0
#define END_GAME_ID 1


class WorldMap : public Scene
{
protected:

	float cursorY;
	HUD* hud;
	map<int, MapNode*> movingMap;
	BOOLEAN hasCreate;
	LPGAMEOBJECT popup;
	GameObjFactory* factory;

	void LoadObjects(vector < tson::Object> objects);
	void LoadLayer(tson::Layer layer, tson::Vector2i tileSize);
	void InitMap();

public:
	WorldMap(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual int GetBackGroundColor() { return BLACK_BACKGROUND_ID; }

	void GameOver();
	void Clear();
	void MoveCursor();
	void PurgeDeletedObjects(std::deque<LPGAMEOBJECT>& list);
	void PurgeDeletedObjects();
	void ExecuteOption();

	bool CanControl() {
		return (popup->IsDeleted());
	}

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

