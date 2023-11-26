// Cup.cpp

#include "Cup.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_cup;

void loadCup() {
    model_cup.Load("Models/cup/kelch12_lowpolyn2.3ds");
}

void renderCup() {
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glScaled(5, 5, 5);
    glTranslatef(0, 0, 0);
    model_cup.Draw();
    glPopMatrix();
}
