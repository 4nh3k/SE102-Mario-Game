#include "MomentumBar.h"

MomentumBar* MomentumBar::__instance = NULL;

MomentumBar* MomentumBar::GetInstance()
{
	if (__instance == NULL) __instance = new MomentumBar(0, 0);
	return __instance;
}

MomentumBar::MomentumBar(float x, float y)
{
	timer = 0;
	nodeFill = 0;
	this->x = x;
	this->y = y;
}
int MomentumBar::GetNode()
{
	return nodeFill;
}
void MomentumBar::Decrease()
{
	if (GetTickCount64() - timer >= DECREASE_TIMEOUT && nodeFill > 0)
	{
		nodeFill--;
		timer = GetTickCount64();
	}
}
void MomentumBar::SetNode(int node)
{
	if (node < nodeFill)
	{
		Decrease();
		return;
	}
	node = (node > 6) ? 6 : node;
	nodeFill = node;
}
void MomentumBar::Render()
{
	for (int i = 0; i < MOMENTUM_NODE_COUNT; i++)
	{
		string aniId = ID_ANI_MOMENTUM_NODE_IDLE;
		if (i < nodeFill)
		{
			aniId = ID_ANI_MOMENTUM_NODE_FILL;
		}
		Animations::GetInstance()->Get(aniId)->Render(x + (i * MOMENTUM_NODE_WIDTH), y);
	}
	string aniId = ID_ANI_MOMENTUM_INDICATOR_IDLE;
	if (nodeFill == MOMENTUM_NODE_COUNT)
	{
		aniId = ID_ANI_MOMENTUM_INDICATOR_FULL;
	}
	Animations::GetInstance()->Get(aniId)->Render(x + (MOMENTUM_NODE_COUNT * MOMENTUM_NODE_WIDTH) + (IDICATOR_WIDTH / 2), y);
}