#pragma once
#include <unordered_map>
#include <d3dx10.h>

#include "Texture.h"

using namespace std;

/*
	Manage texture database
*/
class Textures
{
	static Textures* __instance;

	unordered_map<string, LPTEXTURE> textures;

public:
	Textures();
	void Add(string id, LPCWSTR filePath);
	LPTEXTURE Get(string i);
	void Clear();

	static Textures* GetInstance();
};