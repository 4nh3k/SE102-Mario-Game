#pragma once
#include "GameObject.h"
#include "tileson.hpp"
#include "HUD.h"
#include "GameObjFactory.h"

class EnemyObjFactory : public GameObjFactory
{
public:
	EnemyObjFactory() {}
    GameObject* CreateGameObject(string enemy, tson::Vector2f position, tson::Vector2i* size = nullptr) override;
};

