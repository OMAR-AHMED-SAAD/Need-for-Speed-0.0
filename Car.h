// Car.h
#include "Camera.h"
#include "Coin.h"
#include "Barrier.h"
#include "Star.h"
#include "Cone.h"
#include "Cup.h"
#ifndef CAR_H
#define CAR_H
extern int car_x;
extern int car_y;
extern int car_z;
static bool goLevel2 = true;
extern bool level2;
//enum for tracking game state
enum GameState {
    START,
    PLAYING,
    WIN,
    LOSE
};
extern GameState currentGameState;
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
void collidWithDoor(int score);
void collideWithHuman();
#endif // CAR_H
