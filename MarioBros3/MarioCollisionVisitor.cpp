#include "MarioCollisionVisitor.h"
#include "Mario.h"

void MarioCollisionVisitor::VisitGoomba() {
    m_mario->OnCollisionWithGoomba(e);
}

void MarioCollisionVisitor::VisitCoin() {
    m_mario->OnCollisionWithCoin(e);
}

void MarioCollisionVisitor::VisitPortal() {
    m_mario->OnCollisionWithPortal(e);
}

void MarioCollisionVisitor::VisitQuestionBlock() {
    m_mario->OnCollisionWithQuestionBlock(e);
}

void MarioCollisionVisitor::VisitMushroom() {
    m_mario->OnCollisionWithMushroom(e);
}

void MarioCollisionVisitor::VisitKoopa() {
    m_mario->OnCollisionWithKoopa(e);
}

void MarioCollisionVisitor::VisitSuperLeaf() {
    m_mario->OnCollisionWithSuperLeaf(e);
}

void MarioCollisionVisitor::VisitLaser() {
    m_mario->OnCollisionWithLaser(e);
}

void MarioCollisionVisitor::VisitVenusFireTrap() {
    m_mario->OnCollisionWithVenus(e);
}

void MarioCollisionVisitor::VisitPSwitch() {
    m_mario->OnCollisionWithPSwitch(e);
}

void MarioCollisionVisitor::VisitBrick() {
    m_mario->OnCollisionWithBrick(e);
}

void MarioCollisionVisitor::VisitPiranhaPlant() {
    m_mario->OnCollisionWithPiranhaPlant(e);
}

void MarioCollisionVisitor::VisitPipeline() {
    m_mario->OnCollisionWithPipeline(e);
}

void MarioCollisionVisitor::VisitGoal() {
    m_mario->OnCollisionWithGoal(e);
}

void MarioCollisionVisitor::VisitTheVoid() {
    m_mario->OnCollisionWithTheVoid(e);
}