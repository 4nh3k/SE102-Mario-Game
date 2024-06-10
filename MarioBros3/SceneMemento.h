#pragma once

#include <deque>
class GameObject;
typedef GameObject* LPGAMEOBJECT;

class SceneMemento {
private:
    LPGAMEOBJECT player;
    float camX, camY;
    std::deque<LPGAMEOBJECT> gameObjects;
    std::deque<LPGAMEOBJECT> SFXs;

public:
    SceneMemento(LPGAMEOBJECT player, float camX, float camY,
        std::deque<LPGAMEOBJECT> gameObjects, std::deque<LPGAMEOBJECT> SFXs);

    LPGAMEOBJECT GetPlayer() const { return player; }
    float GetCamX() const { return camX; }
    float GetCamY() const { return camY; }
    std::deque<LPGAMEOBJECT> GetGameObjects() const { return gameObjects; }
    std::deque<LPGAMEOBJECT> GetSFXs() const { return SFXs; }
};
