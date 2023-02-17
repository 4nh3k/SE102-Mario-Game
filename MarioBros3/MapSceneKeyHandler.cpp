#include "MapSceneKeyHandler.h"

#include "debug.h"
#include "Game.h"

#include "MarioMap.h"
#include "WorldMap.h"
#include "MapNode.h"

void MapSceneKeyHandler::OnKeyDown(int KeyCode)
{
	
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	bool isGameOver = HUD::GetInstance()->IsGameOver();
	Game* game = Game::GetInstance();
	if (!game->GetCurrentScene()->CanControl() && !isGameOver) return;
	MarioMap* mario = (MarioMap*)(game->GetCurrentScene())->GetPlayer();
	MapNode* node = mario->GetCurrentNode();
	switch (KeyCode)
	{
	case DIK_DOWN:
		if (isGameOver)
		{
			dynamic_cast<WorldMap*>(game->GetCurrentScene())->MoveCursor();
			break;
		}
		if (node->Bot != NULL && !mario->IsMoving())// && (node->HasClear() || lastKeyCode == DIK_UP))
		{
			lastKeyCode = KeyCode;
			mario->SetCurrentNode(node->Bot);
		}
		break;
	case DIK_UP:
		if (isGameOver)
		{
			dynamic_cast<WorldMap*>(game->GetCurrentScene())->MoveCursor();
			break;
		}
		if (node->Top != NULL && !mario->IsMoving())// && (node->HasClear() || lastKeyCode == DIK_DOWN))
		{
			lastKeyCode = KeyCode;
			mario->SetCurrentNode(node->Top);
		}
		break;
	case DIK_LEFT:
		if (node->Left != NULL && !mario->IsMoving() && !isGameOver)// && (node->HasClear() || lastKeyCode == DIK_RIGHT))
		{
			lastKeyCode = KeyCode;
			mario->SetCurrentNode(node->Left);
		}
		break;
	case DIK_RIGHT:
		if (node->Right != NULL && !mario->IsMoving() && !isGameOver)// && (node->HasClear() || lastKeyCode == DIK_LEFT))
		{
			lastKeyCode = KeyCode;
			mario->SetCurrentNode(node->Right);
		}
		break;
	case DIK_W:
		if (isGameOver)
		{
			dynamic_cast<WorldMap*>(game->GetCurrentScene())->ExecuteOption();
		}
	case DIK_S:
		if (!node->HasClear() && !isGameOver)
		{
			//node->SetClear(true);
			int level = dynamic_cast<MarioMap*>(game->GetCurrentScene()->GetPlayer())->GetLevel();
			game->InitiateSwitchScene(node->GetSceneId());
			game->SwitchScene();
			Mario* mario = dynamic_cast<Mario*>(game->GetCurrentScene()->GetPlayer());
			mario->SetLevel(level,false);
			
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