#pragma once
#include "Scene.h"
class MapSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	MapSceneKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};

