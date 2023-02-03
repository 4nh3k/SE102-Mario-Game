#include "MapSceneKeyHandler.h"

#include "debug.h"
#include "Game.h"

#include "MarioMap.h"
#include "WorldMap.h"
#include "MapNode.h"

void MapSceneKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	MarioMap* mario = (MarioMap*)(Game::GetInstance()->GetCurrentScene())->GetPlayer();
	MapNode* node = mario->GetCurrentNode();
	Game* game = Game::GetInstance();
	switch (KeyCode)
	{
	case DIK_DOWN:
		if (node->Bot != NULL && !mario->IsMoving())// && (node->HasClear() || lastKeyCode == DIK_UP))
		{
			lastKeyCode = KeyCode;
			mario->SetCurrentNode(node->Bot);
		}
		break;
	case DIK_UP:
		if (node->Top != NULL && !mario->IsMoving())// && (node->HasClear() || lastKeyCode == DIK_DOWN))
		{
			lastKeyCode = KeyCode;
			mario->SetCurrentNode(node->Top);
		}
		break;
	case DIK_LEFT:
		if (node->Left != NULL && !mario->IsMoving())// && (node->HasClear() || lastKeyCode == DIK_RIGHT))
		{
			lastKeyCode = KeyCode;
			mario->SetCurrentNode(node->Left);
		}
		break;
	case DIK_RIGHT:
		if (node->Right != NULL && !mario->IsMoving())// && (node->HasClear() || lastKeyCode == DIK_LEFT))
		{
			lastKeyCode = KeyCode;
			mario->SetCurrentNode(node->Right);
		}
		break;
	case DIK_S:
		if (!node->HasClear())
		{
			//node->SetClear(true);
			game->InitiateSwitchScene(node->GetSceneId());
			game->SwitchScene();
		}
		break;
	}


}

void MapSceneKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void MapSceneKeyHandler::KeyState(BYTE* states)
{
	
}