#pragma once
#include "GameObject.h"
#include "tileson.hpp"
#include "HUD.h"
#include "GameObjFactory.h"

class PlatformObjFactory : public GameObjFactory
{
public:
	PlatformObjFactory() {}
	GameObject* CreateGameObject(string enemy, tson::Vector2f position, tson::Vector2i* size) override;
};

