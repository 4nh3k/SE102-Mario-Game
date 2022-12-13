#pragma once

#include "KeyEventHandler.h"
#include <queue>
//#include "GameObject.h"
/*
*  Abstract class for a game scene
*/

class GameObject;
typedef GameObject* LPGAMEOBJECT;

class Scene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;
	LPGAMEOBJECT player;
	std::deque<LPGAMEOBJECT> gameObjects;
public: 
	Scene(int id, LPCWSTR filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
		this->key_handler = NULL;
	}
	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	void AddObject(LPGAMEOBJECT obj) {
		gameObjects.push_front(obj);
	}
	LPGAMEOBJECT GetPlayer() { return player; }
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