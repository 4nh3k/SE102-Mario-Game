#include "Animations.h"
#include "debug.h"
#include "Utils.h"

Animations* Animations::__instance = NULL;

Animations* Animations::GetInstance()
{
	if (__instance == NULL) __instance = new Animations();
	return __instance;
}

void Animations::Add(string id, LPANIMATION ani)
{
	if (animations[id] != NULL)
		DebugOut(L"[WARNING] Animation %d already exists\n", id);

	animations[id] = ani;
}

LPANIMATION Animations::Get(string id)
{
	LPANIMATION ani = animations[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] Animation ID %d not found\n", id);
	return ani;
}

void Animations::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}
void Animations::LoadAnimation(string path)
{
	string xmlPath = path;
	TiXmlDocument doc(xmlPath.c_str());
	if (!doc.LoadFile())
	{
		DebugOut(L"load file=[%s] failed\n", xmlPath);
		return;
	}
	TiXmlElement* root = doc.RootElement();
	string texturePath = root->Attribute("imagePath");
	Textures* textures = Textures::GetInstance();
	textures->Add(1, ToLPCWSTR(texturePath));
	LPTEXTURE texMario = textures->Get(1);
	TiXmlElement* animation = root->FirstChildElement();
	Sprites* sprites = Sprites::GetInstance();
	int i = 0;

	while (animation != NULL)
	{
		string name = animation->Value();
		int frameTime;
		animation->QueryIntAttribute("frameTime", &frameTime);
		string aniID;
		aniID = animation->Attribute("aniID");
		TiXmlElement* frame = animation->FirstChildElement();
		LPANIMATION ani;
		ani = new Animation(100);
		while (frame != NULL)
		{
			string frameID = frame->Attribute("name");
			int top, left, bot, right;
			frame->QueryIntAttribute("x", &left);
			frame->QueryIntAttribute("y", &top);
			frame->QueryIntAttribute("height", &bot);
			frame->QueryIntAttribute("width", &right);
			right += left -1 ;
			bot += top -1;
			sprites->Add(frameID, left, top, right, bot, texMario);
			frame = frame->NextSiblingElement();
			ani->Add(frameID);
		}
		Add(aniID, ani);
		animation = animation->NextSiblingElement();
	}
}