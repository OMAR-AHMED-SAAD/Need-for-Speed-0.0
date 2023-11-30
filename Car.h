// Car.h
#include "Camera.h"
#ifndef CAR_H
#define CAR_H
static int car_x = 0;
static int car_y = 0;
static int car_z = 0;

void loadCar();
void renderCar();
void moveCar(unsigned char key,Camera& camera, bool isFirst);

#endif // CAR_H
