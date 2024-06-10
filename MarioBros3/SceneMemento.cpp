#pragma once
#include "SceneMemento.h"
#include "GameObject.h"
#include <deque>

SceneMemento::SceneMemento(LPGAMEOBJECT player, float camX, float camY,
        std::deque<LPGAMEOBJECT> gameObjects, std::deque<LPGAMEOBJECT> SFXs)
        : player(player ? player->Clone() : nullptr), camX(camX), camY(camY), gameObjects(gameObjects), SFXs(SFXs) {}


