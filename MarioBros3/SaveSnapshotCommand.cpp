#include "SaveSnapshot.h"
#include "Scene.h"

void SaveSnapshotCommand::Execute() {
    if (memento) delete memento; // Clean up previous memento if any
    memento = scene->SaveState();
}

void SaveSnapshotCommand::Undo() {
    if (memento) {
        scene->RestoreState(memento);
    }
}

SaveSnapshotCommand::~SaveSnapshotCommand() {
    delete memento;
}
