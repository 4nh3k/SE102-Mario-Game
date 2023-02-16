#pragma once
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

class Font 
{
	float x, y;
	int charCount;
	std::deque<std::string> String;
public:
	Font(float x, float y, int charCount)
	{
		this->x = x;
		this->y = y;
		this->charCount = charCount;
	}
	void SetString(std::string line);
	void SetPos(float x, float y) { this->x = x; this->y = y; }
	void SetNumber(int num);
	void Render();
};

