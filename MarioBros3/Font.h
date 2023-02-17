#pragma once
#include "GameObject.h"
#include <string>
#include <deque>

#define FONT_WIDTH 8
#define FONT_HEIGHT 8
#define ID_ANI_0 "0"
#define ID_ANI_1 "1"
#define ID_ANI_2 "2"
#define ID_ANI_3 "3"
#define ID_ANI_4 "4"
#define ID_ANI_5 "5"
#define ID_ANI_6 "6"
#define ID_ANI_7 "7"
#define ID_ANI_8 "8"
#define ID_ANI_9 "9"

class Font : public GameObject
{
	int charCount;
	std::deque<std::string> String;
public:
	Font(float x, float y, int charCount) : GameObject(x,y)
	{
		this->charCount = charCount;
	}
	void SetString(std::string line);
	void SetNumber(int num);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

