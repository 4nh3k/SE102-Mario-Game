#pragma once
#include "Scene.h"

class IntroSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	IntroSceneKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};

