// Car.cpp

#include "Coin.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_coin;

void loadCoin() {
    model_coin.Load("Models/coin/Coin.3ds");
}

void renderCoin() {
    glPushMatrix();    
    glTranslatef(2, 0.4, -10);
    glRotated(90, 0, 0, 1);
    glScaled(0.1, 0.1, 0.3);
    model_coin.Draw();
    glPopMatrix();
}
