#pragma once
// Forward declarations for game objects
class Goomba;
class Coin;
class Portal;
class QuestionBlock;
class Mushroom;
class Koopa;
class SuperLeaf;
class ParaGoomba;
class Laser;
class VenusFireTrap;
class PSwitch;
class Brick;
class PiranhaPlant;
class Pipeline;
class Goal;
class CollisionEvent;
class Mario;
typedef CollisionEvent* LPCOLLISIONEVENT;
class TheVoid;

class CollisionVisitor {
protected:
    LPCOLLISIONEVENT e;
public:
    virtual void VisitGoomba()  {}
    virtual void VisitParagoomba()  {}
    virtual void VisitCoin()  {}
    virtual void VisitPortal()  {}
    virtual void VisitQuestionBlock()  {}
    virtual void VisitMushroom()  {}
    virtual void VisitKoopa()  {}
    virtual void VisitSuperLeaf()  {}
    virtual void VisitLaser()  {}
    virtual void VisitVenusFireTrap()  {}
    virtual void VisitPSwitch()  {}
    virtual void VisitBrick()  {}
    virtual void VisitPiranhaPlant()  {}
    virtual void VisitPipeline()  {}
    virtual void VisitGoal()  {}
    virtual void VisitTheVoid()  {}


    CollisionVisitor(LPCOLLISIONEVENT _e) : e(_e) {}
};