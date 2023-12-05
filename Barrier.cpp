// Car.cpp

#include "Barrier.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_barrier;

void loadBarrier() {
    model_barrier.Load("Models/concrete_barrier/Concrete_Barricade.3ds");
}

void renderBarrier() {
    glPushMatrix();    
    glTranslatef(-2, 0, -5);
    glRotated(90, 0, 1, 0);
    glScaled(0.5, 0.5, 0.5);
    model_barrier.Draw();
    glPopMatrix();
}
