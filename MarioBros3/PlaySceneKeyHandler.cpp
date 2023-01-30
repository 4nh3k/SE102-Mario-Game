#include "PlaySceneKeyHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void PlaySceneKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	Mario* mario = (Mario *)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_TANOOKI);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
	case DIK_A:
		if (mario->IsTanooki())
			mario->SetState(MARIO_STATE_TAIL_WHACK);
		break;
	case DIK_ESCAPE:
		if (Game::GetInstance()->GetCurrentScene()->IsPause())
		{
			Game::GetInstance()->GetCurrentScene()->Continue();
		}
		else Game::GetInstance()->GetCurrentScene()->Pause();
	}

}

void PlaySceneKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	Mario* mario = (Mario*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		if (mario->IsHolding())
			mario->SetState(MARIO_STATE_KICK);
		else
		{
			mario->SetState(MARIO_STATE_RELEASE_RUN);
		}
		break;
	}
}

void PlaySceneKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = Game::GetInstance();
	Mario* mario = (Mario*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			if (!mario->IsHolding())
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			else mario->SetState(MARIO_STATE_RUNNING_HOLD_RIGHT);

		}
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			if (!mario->IsHolding())
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			else mario->SetState(MARIO_STATE_RUNNING_HOLD_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}