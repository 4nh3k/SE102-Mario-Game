#pragma once
#include "GameObject.h"

#define ID_ANI_PIRANHA_PLANT_IDLE "green_piranha_plant_idle"
#define GO_DOWN_TIME 500
#define GO_UP_TIME 1000

#define FAR_RANGE 80
#define PIRANHA_PLANT_SPEED 0.03f
#define PIRANHA_PLANT_HEIGHT 32
#define PIRANHA_PLANT_WIDTH 16
class PiranhaPlant :
    public GameObject
{
protected:
	float oldY;
	ULONGLONG timer;
	ULONGLONG updownTimer;
	bool isUp;
	bool isDown;
	bool moving;
	float mx, my;
public:
	PiranhaPlant(float x, float y) : GameObject(x, y)
	{
		oldY = y;
		updownTimer = GetTickCount64();
		isUp = false;
		moving = false;
		isDown = true;
		vy = -PIRANHA_PLANT_SPEED;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() {
		return (moving || !isDown);
	};	
	void Accept(CollisionVisitor* visitor) {
		visitor->VisitPiranhaPlant();
	}
	virtual int IsBlocking(float nx, float ny) { return 0; }
};
