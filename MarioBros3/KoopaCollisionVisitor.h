#pragma once
#include "CollisionVisitor.h"

class KoopaCollisionVisitor : public CollisionVisitor
{
public:
    KoopaCollisionVisitor(Koopa* koopa, LPCOLLISIONEVENT _e) : _koopa(koopa), CollisionVisitor(_e) {}
    KoopaCollisionVisitor(LPCOLLISIONEVENT _e) : CollisionVisitor(_e) {}
    virtual void VisitGoomba();
    virtual void VisitQuestionBlock();
    virtual void VisitKoopa();
    virtual void VisitVenusFireTrap();
    virtual void VisitBrick();
    virtual void VisitPiranhaPlant();

private:
    Koopa* _koopa;
};

//void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
//void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
//void OnCollisionWithVenus(LPCOLLISIONEVENT e);
//void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
//void OnCollisionWithBrick(LPCOLLISIONEVENT e);
//void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);