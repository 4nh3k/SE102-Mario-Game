#include "Koopa.h"

#define ID_ANI_PARA_KOOPA_FLY_LEFT "parakoopa_fly_left"
#define ID_ANI_PARA_KOOPA_FLY_RIGHT "parakoopa_fly_right"

#define PARA_KOOPA_FLY_SPEED_Y 0.22f

class ParaKoopa : public Koopa
{
protected:
	ULONGLONG timer;
	bool hasWing;
	bool isFlying;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	ParaKoopa(float x, float y) : Koopa(x, y) { hasWing = true; isFlying = false; };
	bool HasWing() { return hasWing; }
	void SetWing(bool hasWing) { this->hasWing = hasWing; }
};
