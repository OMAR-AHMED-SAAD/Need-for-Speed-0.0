// Car.h
#include "Camera.h"
#include "Coin.h"
#include "Barrier.h"
#include "Star.h"
#include "Cone.h"
#include "Cup.h"
#ifndef CAR_H
#define CAR_H
static int car_x = 0;
static int car_y = 0;
static int car_z = 0;

void loadCar();
void renderCar();
void moveCar(unsigned char key,Camera& camera, bool isFirst);
float euclideanDistance(float x1, float y1, float z1, float x2, float y2, float z2);
void collideWithCoins(int* score);
bool collideWithBarrierZ();
bool collideWithBarrierX();
void collideWithStars(int* score);
bool collideWithConeZ();
bool collideWithConeX();
void collideWithCup();
#endif // CAR_H
