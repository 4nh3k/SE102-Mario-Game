#include "Font.h"
#include "Animations.h"
#include "string"
void Font::SetNumber(int num)
{
	String.clear();
	int numCount = 0;
	while (num != 0)
	{
		numCount++;
		String.push_front(to_string(num % 10));
		num /= 10;
	}
	for (int i = 0; i < charCount - numCount; i++)
	{
		String.push_front("0");
	}
}
void Font::Render()
{
	std::deque<std::string> tmp = String;
	int count = 0;
	while (!tmp.empty())
	{
		char c = tmp.front()[0];
		if(( c>= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '!')
			Animations::GetInstance()->Get(tmp.front())->Render(x + count * FONT_WIDTH, y);
		count++;
		tmp.pop_front();
	}
}
void Font::SetString(std::string line)
{
	String.clear();
	for (size_t i = 0; i < line.size(); i++)
	{
		string tmp(1, line[i]);
		String.push_back(tmp);
	}
}