#pragma once
#include "GameObject.h"
#include "tileson.hpp"
#include "HUD.h"

class GameObjFactory
{
public:
	virtual GameObject* CreateGameObject(string enemy, tson::Vector2f position, tson::Vector2i* size = nullptr) = 0;
};

