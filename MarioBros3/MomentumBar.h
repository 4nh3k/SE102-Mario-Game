#pragma once
#define ID_ANI_MOMENTUM_NODE_IDLE "momentum_node_idle"
#define ID_ANI_MOMENTUM_NODE_FILL "momentum_node_run"
#define ID_ANI_MOMENTUM_INDICATOR_IDLE "momentum_indicator_idle"
#define ID_ANI_MOMENTUM_INDICATOR_FULL "momentum_indicator_full"

#define DECREASE_TIMEOUT 500
#define FLYING_TIMEOUT 5000
#define IDICATOR_WIDTH 8
#define MOMENTUM_NODE_WIDTH 8
#define MOMENTUM_NODE_HEIGHT 7
#define MOMENTUM_NODE_COUNT 6
#include "Animations.h"
#include "string"

class MomentumBar
{
	static MomentumBar* __instance;
	float x, y;
	DWORD timer;
	BOOL stopDecrease;
	int nodeFill;
public:
	MomentumBar(float x, float y);
	void SetPos(float x, float y) { this->x = x; this->y = y; }
	void SetNode(int node);
	int GetNode();
	void Render();
	void StartTimer();
	void Decrease();
	void IndiactorFull();
	static MomentumBar* GetInstance();
};

