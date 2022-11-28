#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Animations.h"
#include "tinyxml.h"
#include "debug.h"
#include "Textures.h"

#define TEXTURES_DIR L""
#define ANIMATIONS_PATH_MARIO "textures\\mario.xml"

class Animations
{
	static Animations* __instance;

	unordered_map<string, LPANIMATION> animations;

public:
	void Add(string id, LPANIMATION ani);
	LPANIMATION Get(string id);
	void Clear();
	void LoadAnimation(string path);
	static Animations* GetInstance();
};