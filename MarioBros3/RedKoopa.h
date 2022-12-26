#pragma once
#include "Koopa.h"
#include "GhostBlock.h"

#define ID_ANI_RED_KOOPA_WALK_RIGHT "red_koopa_walk_right"
#define ID_ANI_RED_KOOPA_WALK_LEFT "red_koopa_walk_left"
#define ID_ANI_RED_KOOPA_KICKED "red_koopa_kicked"
#define ID_ANI_RED_KOOPA_HIDE "red_koopa_hide"
#define ID_ANI_RED_KOOPA_WAKE_UP "red_koopa_wake_up"

#define ID_ANI_RED_KOOPA_KICKED_UPSIDE_DOWN "red_koopa_kicked_up_side_down"
#define ID_ANI_RED_KOOPA_HIDE_UPSIDE_DOWN "red_koopa_hide_up_side_down"
#define ID_ANI_RED_KOOPA_WAKE_UP_UPSIDE_DOWN "red_koopa_wake_up_up_side_down"


class RedKoopa :
    public Koopa
{
    LPGAMEOBJECT ghostBlock;
public:
    RedKoopa(float x, float y) : Koopa(x,y)
    {
        ghostBlock = new GhostBlock(x + KOOPA_BBOX_WIDTH/2 , y);
        Game::GetInstance()->GetCurrentScene()->AddObject(ghostBlock);
    }
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual string GetAniId();
    virtual string GetAniIdUpsideDown();
};

