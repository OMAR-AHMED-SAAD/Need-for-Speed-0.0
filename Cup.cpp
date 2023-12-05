// Cup.cpp

#include "Cup.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_cup;

float cup_coords[3] = { 0.0f, 0.5f, -270.0f };
bool cup_collected = false;
void loadCup() {
    model_cup.Load("Models/cup/kelch12_lowpolyn2.3ds");
}

void renderCup() {
    if(cup_collected) return;
    glPushMatrix();    
    glTranslatef(cup_coords[0], cup_coords[1], cup_coords[2]);
    glRotated(90, 0, 1, 0);
    glScaled(3, 3, 3);
    model_cup.Draw();
    glPopMatrix();
}
