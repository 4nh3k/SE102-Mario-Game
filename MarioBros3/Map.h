#pragma once
#include "Textures.h"
#include "Sprites.h"
#include "tileson.hpp"
#include "debug.h"
#include "Utils.h"
#include "GameObject.h"
#include "Game.h"
#include "Platform.h"
class Map 
{
protected:
	vector<pair<string, pair<float, float>>> drawPos;
public:
	Map(string mapPath);
	void Load(string mapPath);
	void Render();
};

