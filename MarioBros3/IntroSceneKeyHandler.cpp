#include "IntroSceneKeyHandler.h"
#include "IntroScene.h"
#include "debug.h"
#include "Game.h"

void IntroSceneKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	Game* game = Game::GetInstance();
	IntroScene* scene = (IntroScene*)(Game::GetInstance()->GetCurrentScene());
	switch (KeyCode)
	{
	case DIK_Q:
		scene->MoveCursor();
		break;
	case DIK_W:
		game->InitiateSwitchScene(WORLD_MAP_SCENE_ID);
		game->SwitchScene();
		break;
	}


}

void IntroSceneKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void IntroSceneKeyHandler::KeyState(BYTE* states)
{

}