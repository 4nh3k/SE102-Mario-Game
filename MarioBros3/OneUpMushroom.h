#pragma once
#include "Mushroom.h"
#define ID_ANI_1UP_MUSHROOM "1up_mushroom"

class OneUpMushroom :
    public Mushroom
{
public:
    OneUpMushroom(float x, float y) : Mushroom(x, y){}
	void Render()
	{
		Animations* animations = Animations::GetInstance();
		animations->Get(ID_ANI_1UP_MUSHROOM)->Render(x, y);

		//RenderBoundingBox();
	}

};

