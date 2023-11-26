// Car.cpp

#include "Star.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_star;

void loadStar() {
    model_star.Load("Models/star/star.3ds");
}

void renderStar() {
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glScaled(1, 1, 1);
    glTranslatef(0, 0, 2);
    model_star.Draw();
    glPopMatrix();
}