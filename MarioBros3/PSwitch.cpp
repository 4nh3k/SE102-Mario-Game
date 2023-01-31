#include "PSwitch.h"
#include "Animations.h"
#include "Brick.h"
#include "Coin.h"

PSwitch::PSwitch(float x, float y) : GameObject(x, y) 
{
	state = PSWITCH_STATE_IDLE;
	sfx = new SFX(x, y, ID_ANI_VANISH);
	Game::GetInstance()->GetCurrentScene()->AddSFX(sfx);
	startRender = false;
}
void PSwitch::Render()
{
	string aniId = ID_ANI_PSWITCH_IDLE;
	if (startRender)
	{
		if (state == PSWITCH_STATE_HIT)
			aniId = ID_ANI_PSWITCH_HIT;
		Animations::GetInstance()->Get(aniId)->Render(x,y);
	}
	RenderBoundingBox();
}

void PSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(startRender == false)
		if (sfx->IsDeleted())
		{
			startRender = true;
		}
}

void PSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float height = (state == PSWITCH_STATE_IDLE) ? PSWITCH_IDLE_BBOX_HEIGHT : PSWITCH_HIT_BBOX_HEIGHT;
	l = x - PSWITCH_BBOX_WIDTH / 2;
	t = y - height / 2;
	r = l + PSWITCH_BBOX_WIDTH;
	b = t + height;
}
void PSwitch::SetState(int state)
{
	if (state == PSWITCH_STATE_HIT)
	{
		y += (PSWITCH_IDLE_BBOX_HEIGHT - PSWITCH_HIT_BBOX_HEIGHT) / 2;
		TurnBrickIntoCoin();
	}
	GameObject::SetState(state);
}
void PSwitch::TurnBrickIntoCoin()
{
	std::deque<LPGAMEOBJECT> gameObjects = Game::GetInstance()->GetCurrentScene()->GetGameObjects();
	for (auto& obj : gameObjects)
	{
		if (dynamic_cast<Brick*>(obj))
		{
			float x, y;
			obj->GetPosition(x, y);
			obj->Delete();
			Game::GetInstance()->GetCurrentScene()->AddObject(new Coin(x, y));
		}
	}
}