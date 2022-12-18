#pragma once
#include "Koopa.h"
#include "GhostBlock.h"
class RedKoopa :
    public Koopa
{
    LPGAMEOBJECT ghostBlock;
public:
    RedKoopa(float x, float y) : Koopa(x,y)
    {
        ghostBlock = new GhostBlock(x + KOOPA_BBOX_WIDTH/2 + 5, y);
        Game::GetInstance()->GetCurrentScene()->AddObject(ghostBlock);
    }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

