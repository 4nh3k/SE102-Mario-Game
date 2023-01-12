#pragma once
#include "SFX.h"

#define ID_ANI_BRICK_PARTICLE "brick_particle"
#define BRICK_PARTICLE_GRAVITY 0.001f
#define BRICK_PARTICLE_HIGH_SPEED_Y 0.25f
#define BRICK_PARTICLE_SLOW_SPEED_Y 0.15f
#define BRICK_PARTICLE_SPEED_X 0.08f
#define BRICK_PARTICLE_TIMEOUT 1500

class BrickParticle : public SFX
{
public:
	BrickParticle(float x, float y, bool flyHigh, int nx ,string aniId = ID_ANI_BRICK_PARTICLE) : SFX(x, y, aniId) 
	{ 
		vy = (flyHigh) ? -BRICK_PARTICLE_HIGH_SPEED_Y : -BRICK_PARTICLE_SLOW_SPEED_Y;
		vx = nx * BRICK_PARTICLE_SPEED_X;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		vy += BRICK_PARTICLE_GRAVITY * dt;

		x += vx * dt;
		y += vy * dt;

		if (GetTickCount64() - timer >= BRICK_PARTICLE_TIMEOUT)
		{
			this->Delete();
		}

	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	int IsBlocking(float nx, float ny) { return 0; }
};
