#pragma once

#include "KeyEventHandler.h"
#include <queue>
#include "SceneMemento.h"
#include "CommandManager.h"
#include "SaveSnapshot.h"
//#include "GameObject.h"
/*
*  Abstract class for a game scene
*/
class TileMap;
class GameObject;
typedef GameObject* LPGAMEOBJECT;

class Scene
{
protected:
	TileMap* tileMap;
	LPKEYEVENTHANDLER key_handler;
	int id;
	bool pauseUpdate;
	LPCWSTR sceneFilePath;
	LPGAMEOBJECT player;
	float camY;
	float camX;
	CommandManager commandManager;
	std::deque<LPGAMEOBJECT> SFXs;
	std::deque<LPGAMEOBJECT> gameObjects;
	std::deque<LPGAMEOBJECT> lowLayer;
public: 
	Scene(int id, LPCWSTR filePath)
	{
		this->player = NULL;
		this->id = id;
		this->sceneFilePath = filePath;
		this->key_handler = NULL;
		this->pauseUpdate = false;
	}
	SceneMemento* SaveState() {
		return new SceneMemento(player,camX, camY, gameObjects, SFXs);
	}
	void RestoreState(SceneMemento* memento) {
		this->player = memento->GetPlayer();
		this->camX = memento->GetCamX();
		this->camY = memento->GetCamY();
		this->gameObjects = memento->GetGameObjects();
		this->SFXs = memento->GetSFXs();
	}

	void SaveSnapshot() {
		SaveSnapshotCommand* command = new SaveSnapshotCommand(this);
		commandManager.ExecuteCommand(command);
	}

	void Undo() {
		commandManager.Undo();
	}


	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	void AddObject(LPGAMEOBJECT obj) {
		gameObjects.push_front(obj);
	}
	void AddSFX(LPGAMEOBJECT sfx)
	{
		SFXs.push_back(sfx);
	}
	void SetCamLimitPos(int camX, int camY) {
		this->camX = camX;
		this->camY = camY;
	}

	LPGAMEOBJECT GetPlayer() { return player; }
	std::deque<LPGAMEOBJECT> GetGameObjects() { return gameObjects; }
	bool IsPause() { return pauseUpdate; }
	void Pause() { pauseUpdate = true; }
	void Continue() { pauseUpdate = false; }
	virtual bool CanControl() { return true; }
	virtual void SetBackGroundColor(int colorId) {}
	virtual int GetBackGroundColor() = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
};
typedef Scene * LPSCENE;


class CSceneKeyHandler : public KeyEventHandler
{
protected: 
	Scene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :KeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;