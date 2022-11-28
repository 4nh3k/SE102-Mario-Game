#include "Sprites.h"
#include "Game.h"
#include "debug.h"

Sprites* Sprites::__instance = NULL;

Sprites* Sprites::GetInstance()
{
	if (__instance == NULL) __instance = new Sprites();
	return __instance;
}

void Sprites::Add(string id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE Sprites::Get(string id)
{
	return sprites[id];
}

/*
	Clear all loaded sprites
*/
void Sprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}