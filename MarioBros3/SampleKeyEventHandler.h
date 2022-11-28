#pragma once

#include "Scene.h"

class SampleKeyHandler: public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	SampleKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
