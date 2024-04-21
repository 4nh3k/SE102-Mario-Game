#include "KoopaCollisionVisitor.h"
#include "Koopa.h"

void KoopaCollisionVisitor::VisitGoomba() {
    _koopa->OnCollisionWithGoomba(e);
}


void KoopaCollisionVisitor::VisitQuestionBlock() {
    _koopa->OnCollisionWithQuestionBlock(e);
}

void KoopaCollisionVisitor::VisitKoopa() {
    _koopa->OnCollisionWithKoopa(e);
}

void KoopaCollisionVisitor::VisitVenusFireTrap() {
    _koopa->OnCollisionWithVenus(e);
}


void KoopaCollisionVisitor::VisitBrick() {
    _koopa->OnCollisionWithBrick(e);
}

void KoopaCollisionVisitor::VisitPiranhaPlant() {
    _koopa->OnCollisionWithPiranhaPlant(e);
}
