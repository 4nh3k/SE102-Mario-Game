#pragma once
#include "GameObject.h"

#define ID_ANI_VENUS_IDLE_RIGHT_UP "venus_idle_right_up"
#define ID_ANI_VENUS_IDLE_LEFT_UP "venus_idle_left_up"

#define ID_ANI_VENUS_IDLE_RIGHT_DOWN "venus_idle_right_down"
#define ID_ANI_VENUS_IDLE_LEFT_DOWN "venus_idle_left_down"

#define ID_ANI_VENUS_CLOSE_RIGHT_UP "venus_close_right_up"
#define ID_ANI_VENUS_CLOSE_LEFT_UP "venus_close_left_up"

#define ID_ANI_VENUS_CLOSE_RIGHT_DOWN "venus_close_right_down"
#define ID_ANI_VENUS_CLOSE_LEFT_DOWN "venus_close_left_down"

#define LASER_AIM_TIME 2000
#define LASER_SHOOT_TIME 2000
#define LASER_OFFSET_Y -6
#define GO_DOWN_TIME 5000
#define FAR_RANGE 80
#define VENUS_SPEED 0.03f
#define VENUS_HEIGHT 32
#define VENUS_WIDTH 16

class VenusFireTrap :
    public GameObject
{
protected:
	float oldY;
	ULONGLONG timer;
	ULONGLONG updownTimer;
	bool isUp;
	bool isDown;
	bool hasShoot;
	bool moving;
	float mx, my;
	void ShootLaser();
public:
	VenusFireTrap(float x, float y) : GameObject(x, y)
	{ 
		oldY = y;
		timer = GetTickCount64(); 
		updownTimer = GetTickCount64();
		isUp = false; 
		hasShoot = false;
		moving = false;
		isDown = true;
		vy = -VENUS_SPEED; 
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() {
		return (moving || !isDown);
	};
	virtual int IsBlocking(float nx, float ny) { return 0; }
	void Accept(CollisionVisitor* visitor) {
		visitor->VisitVenusFireTrap();
	}
};

