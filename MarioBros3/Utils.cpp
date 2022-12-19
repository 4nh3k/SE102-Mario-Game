#include <Windows.h>

#include "Utils.h"

vector<string> split(string line, string delimeter)
{
	vector<string> tokens;
	size_t last = 0; size_t next = 0;
	while ((next = line.find(delimeter, last)) != string::npos)
	{
		tokens.push_back(line.substr(last, next - last));
		last = next + 1;
	}
	tokens.push_back(line.substr(last));

	return tokens;
}

/*
char * string to wchar_t* string.
*/
wstring ToWSTR(string st)
{
	const char *str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t * wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring wstr(wcstring);

	// delete wcstring   // << can I ? 
	return wstr;
}

/*
	Convert char* string to wchar_t* string.
*/
LPCWSTR ToLPCWSTR(string st)
{
	const char *str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t * wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring *w = new wstring(wcstring);

	// delete wcstring   // << can I ? 
	return w->c_str();
}

/*
	Get int property of tiled object
*/
int GetProperty(tson::Object obj, string propName)
{
	if (obj.getProperties().hasProperty(propName))
	{
		tson::Property* prop = obj.getProp(propName);
		return any_cast<int>(prop->getValue());
	}
	return NO_PROP;
}

string GetProperty(tson::Layer layer, string propName)
{
	if (layer.getProperties().hasProperty(propName))
	{
		tson::Property* prop = layer.getProp(propName);
		return any_cast<string>(prop->getValue());
	}
	return "";
}

/*
	Get in game position of tiled object
*/
tson::Vector2f ToInGamePos(tson::Object obj)
{
	tson::Vector2f inGamePos = tson::Vector2f(0.0f,0.0f);
	tson::Vector2i pos = obj.getPosition();
	tson::Vector2i size = obj.getSize();
	switch (obj.getObjectType())
	{
	case tson::ObjectType::Point:
		inGamePos.x = ((pos.x / 16) * 16 + 8);
		inGamePos.y = ((pos.y / 16) * 16 + 8);
		break;
	case tson::ObjectType::Rectangle:
		inGamePos.x = pos.x + size.x / 2;
		inGamePos.y = pos.y + size.y / 2;
		break;
	default:
		inGamePos.x = pos.x;
		inGamePos.y = pos.y;
		break;
	}
	return inGamePos;
}