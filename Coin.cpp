// Car.cpp

#include "Coin.h"
#include "Model_3DS.h"
#include "glut.h"
#include <math.h>

Model_3DS model_coin;
bool coin_collected[5] = { false, false, false, false, false };
float coin_coords[5][3] = {
       {-2, 0.4, -10},
        {-1, 0.4, -50},
        {0, 0.4, -100},
        {1, 0.4, -150},
        {2, 0.4, -200}
};
void loadCoin() {
    model_coin.Load("Models/coin/Coin.3ds");
}

void renderCoin(float translate_x, float translate_y, float translate_z) {
    glPushMatrix();
    //2, 0.4,-10
    glTranslatef(translate_x, translate_y, translate_z);
    glRotated(90, 0, 1, 0);
    glRotated(90, 0, 0, 1);
    glScaled(0.1, 0.1, 0.1);
    model_coin.Draw();
    glPopMatrix();
}

void renderCoins() {
    for (int i = 0; i < 5; i++) {
        //printf("Coin %d: %d\n", i, coin_collected[i]);
        if (!coin_collected[i]) {
		    renderCoin(coin_coords[i][0], coin_coords[i][1], coin_coords[i][2]);
        }
	}
}



