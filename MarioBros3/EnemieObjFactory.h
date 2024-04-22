#pragma once
#include "GameObject.h"
#include "GameObjFactory.h"
#include "tileson.hpp"
#include "HUD.h"

class EnemieObjFactory : GameObjFactory
{
public:
	virtual GameObject CreateEnemies(string enemie, tson::Vector2f position);
};

