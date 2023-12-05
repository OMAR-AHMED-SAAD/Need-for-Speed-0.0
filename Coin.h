// Coin.h

#ifndef COIN_H
#define COIN_H

extern float coin_coords[5][3];
extern bool coin_collected[5];


void loadCoin();
void renderCoin(float translate_x, float translate_y, float translate_z);
void renderCoins();


#endif // COIN_H