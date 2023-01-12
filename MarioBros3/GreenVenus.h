#pragma once
#include "VenusFireTrap.h"

#define ID_ANI_GREEN_VENUS_IDLE_RIGHT_UP "green_venus_idle_right_up"
#define ID_ANI_GREEN_VENUS_IDLE_LEFT_UP "green_venus_idle_left_up"

#define ID_ANI_GREEN_VENUS_IDLE_RIGHT_DOWN "green_venus_idle_right_down"
#define ID_ANI_GREEN_VENUS_IDLE_LEFT_DOWN "green_venus_idle_left_down"

#define ID_ANI_GREEN_VENUS_CLOSE_RIGHT_UP "green_venus_close_right_up"
#define ID_ANI_GREEN_VENUS_CLOSE_LEFT_UP "green_venus_close_left_up"

#define ID_ANI_GREEN_VENUS_CLOSE_RIGHT_DOWN "green_venus_close_right_down"
#define ID_ANI_GREEN_VENUS_CLOSE_LEFT_DOWN "green_venus_close_left_down"


class GreenVenus :
    public VenusFireTrap
{
public:
	GreenVenus(float x, float y) : VenusFireTrap(x,y) {}
	void Render()
	{
		string aniID;
		if (!moving)
			if (x > mx) // look left
			{
				if (y > my) // look up
				{
					aniID = ID_ANI_GREEN_VENUS_IDLE_LEFT_UP;
				}
				else // look down
				{
					aniID = ID_ANI_GREEN_VENUS_IDLE_LEFT_DOWN;
				}
			}
			else // look right
			{
				if (y > my)
				{
					aniID = ID_ANI_GREEN_VENUS_IDLE_RIGHT_UP;
				}
				else
				{
					aniID = ID_ANI_GREEN_VENUS_IDLE_RIGHT_DOWN;
				}
			}
		else
		{
			if (x > mx) // look left
			{
				if (y > my) // look up
				{
					aniID = ID_ANI_GREEN_VENUS_CLOSE_LEFT_UP;
				}
				else // look down
				{
					aniID = ID_ANI_GREEN_VENUS_CLOSE_LEFT_DOWN;
				}
			}
			else // look right
			{
				if (y > my)
				{
					aniID = ID_ANI_GREEN_VENUS_CLOSE_RIGHT_UP;
				}
				else
				{
					aniID = ID_ANI_GREEN_VENUS_CLOSE_RIGHT_DOWN;
				}
			}
		}
		Animations::GetInstance()->Get(aniID)->Render(x, y);
		RenderBoundingBox();
	}

};

