#pragma once
#include "GameObject.h"

#define ANI_ID_GOAL "goal"
#define ANI_ID_FLOWER_ROTATE "flower_rotate"
#define ANI_ID_MUSHROOM_ROTATE "mushroom_rotate"
#define ANI_ID_STAR_ROTATE "star_rotate"

#define RAISE_UP_SPEED 0.1f

#define CARD_FLOWER_ID	0
#define CARD_STAR_ID	1
#define CARD_MUSHROOM_ID	2

class Goal :
    public GameObject
{
	int rewardId;
	bool hit;
	float width;
	float height;
public:
	Goal(float x, float y, float w, float h);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetReward();
	void RenderBoundingBox(void);
	bool HasHit() { return hit; }
	void Accept(CollisionVisitor* visitor) {
		visitor->VisitGoal();
	}
	int IsBlocking(float nx, float ny) { return 0; }
};

