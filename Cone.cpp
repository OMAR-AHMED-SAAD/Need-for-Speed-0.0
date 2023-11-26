// Car.cpp

#include "Cone.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_cone;

void loadCone() {
    model_cone.Load("Models/cone/cone.3ds");
}

void renderCone() {
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glScaled(0.5, 0.5, 0.5);
    glTranslatef(0, 0, 2);
    model_cone.Draw();
    glPopMatrix();
}
