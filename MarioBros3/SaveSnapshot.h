#pragma once

#include "Command.h"
#include "SceneMemento.h"

class Scene;
typedef Scene* LPSCENE;

class SaveSnapshotCommand : public Command {
private:
    LPSCENE scene;
    SceneMemento* memento;

public:
    SaveSnapshotCommand(LPSCENE scene) : scene(scene), memento(nullptr) {}

    void Execute() override;
    void Undo() override;
    ~SaveSnapshotCommand();
};
