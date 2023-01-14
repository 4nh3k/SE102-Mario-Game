#include "Font.h"
#include "Animations.h"
void Font::SetNumber(int num)
{
	int numCount = 0;
	while (num != 0)
	{
		numCount++;
		Number.push(to_string(num % 10));
		num /= 10;
	}
	for (int i = 0; i < charCount - numCount; i++)
	{
		Number.push("0");
	}
}
void Font::Render()
{
	int count = 0;
	while (!Number.empty())
	{
		if(Number.top() != "")
			Animations::GetInstance()->Get(Number.top())->Render(x + count * FONT_WIDTH, y);
		count++;
		Number.pop();
	}
}