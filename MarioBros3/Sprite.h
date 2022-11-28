#pragma once

#include "Texture.h"
#include "Game.h"

class Sprite
{
	string id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	Sprite(string id, int left, int top, int right, int bottom, LPTEXTURE tex);

	void Draw(float x, float y);
};

typedef Sprite* LPSPRITE;