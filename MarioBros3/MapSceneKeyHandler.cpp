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
	switch (KeyCode)
	{
	case DIK_DOWN:
		if (node->Bot != NULL && !mario->IsMoving())
			mario->SetCurrentNode(node->Bot);
		break;
	case DIK_UP:
		if (node->Top != NULL && !mario->IsMoving())
			mario->SetCurrentNode(node->Top);
		break;
	case DIK_LEFT:
		if (node->Left != NULL && !mario->IsMoving())
			mario->SetCurrentNode(node->Left);
		break;
	case DIK_RIGHT:
		if (node->Right != NULL && !mario->IsMoving())
			mario->SetCurrentNode(node->Right);
		break;
	case DIK_ESCAPE:
		if (Game::GetInstance()->GetCurrentScene()->IsPause())
		{
			Game::GetInstance()->GetCurrentScene()->Continue();
		}
		else Game::GetInstance()->GetCurrentScene()->Pause();
	}

}

void MapSceneKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void MapSceneKeyHandler::KeyState(BYTE* states)
{
	
}