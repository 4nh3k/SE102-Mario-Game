#include "PointSFX.h"
void PointSFX::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	if (GetTickCount64() - timer >= DELETE_TIME)
	{
		this->Delete();
	}
}
string PointSFX::GetAniId(int point)
{
	string aniId = ID_ANI_100POINT;
	switch (point)
	{
	case 100:
		aniId = ID_ANI_100POINT;
		break;
	case 200:
		aniId = ID_ANI_200POINT;
		break;
	case 400:
		aniId = ID_ANI_400POINT;
		break;
	case 800:
		aniId = ID_ANI_800POINT;
		break;
	case 1000:
		aniId = ID_ANI_1000POINT;
		break;
	case 2000:
		aniId = ID_ANI_2000POINT;
		break;
	case 4000:
		aniId = ID_ANI_4000POINT;
		break;
	case 8000:
		aniId = ID_ANI_8000POINT;
		break;
	case 0:
		aniId = ID_ANI_1UP;
		break;
	default:
		aniId = "";
		break;
	}
	return aniId;
}