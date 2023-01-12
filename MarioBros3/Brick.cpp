#include "Brick.h"
#include "BrickParticle.h"


void Brick::Render()
{
	Animations* animations = Animations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	RenderBoundingBox();
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}
void Brick::Break()
{
	Game::GetInstance()->GetCurrentScene()->AddSFX(new BrickParticle(x,y,true,-1));
	Game::GetInstance()->GetCurrentScene()->AddSFX(new BrickParticle(x, y, true, 1));
	Game::GetInstance()->GetCurrentScene()->AddSFX(new BrickParticle(x, y, false, 1));
	Game::GetInstance()->GetCurrentScene()->AddSFX(new BrickParticle(x, y, false, -1));

	this->Delete();
}