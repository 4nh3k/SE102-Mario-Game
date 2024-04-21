#pragma once
#include "CollisionVisitor.h"


class MarioCollisionVisitor : public CollisionVisitor
{
public:
    MarioCollisionVisitor(Mario* mario, LPCOLLISIONEVENT _e) : m_mario(mario), CollisionVisitor(_e) {}
    MarioCollisionVisitor(LPCOLLISIONEVENT _e) : CollisionVisitor(_e) {}

    virtual void VisitGoomba();
    virtual void VisitCoin();
    virtual void VisitPortal();
    virtual void VisitQuestionBlock();
    virtual void VisitMushroom();
    virtual void VisitKoopa();
    virtual void VisitSuperLeaf();
    virtual void VisitLaser();
    virtual void VisitVenusFireTrap();
    virtual void VisitPSwitch();
    virtual void VisitBrick();
    virtual void VisitPiranhaPlant();
    virtual void VisitPipeline();
    virtual void VisitGoal();
    virtual void VisitTheVoid();


private:
    Mario* m_mario;
};

