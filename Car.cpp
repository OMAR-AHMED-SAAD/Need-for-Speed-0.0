// Car.cpp
#include <iostream>
#include "Car.h"
#include "Model_3DS.h"
#include "glut.h"
#include <algorithm>
#include <math.h>
Model_3DS model_car;

int speed_car = 1;
void loadCar() {
    model_car.Load("Models/car/Crysler_new_yorker_1980.3ds");
}

void renderCar() {
    glPushMatrix();
    glTranslatef(car_x, car_y, car_z);  
    glRotated(90, 0, 1, 0);
    glScaled(0.5,0.5,0.5);
    glTranslatef(0,0, 2);  //constant
    model_car.Draw();
    glPopMatrix();
}

void moveCar(unsigned char key, Camera& camera, bool isFirst) {

    switch (key) {
    case GLUT_KEY_LEFT:
        car_x -= speed_car; // Move left
        if (collideWithBarrierX())
        {
            car_x += speed_car;
        }
        car_x = car_x >= -3 ? car_x : -3;
        
        break;
    case GLUT_KEY_RIGHT:
        car_x += speed_car; // Move right
        if (collideWithBarrierX())
        {
            car_x -= speed_car;
        }
        car_x = car_x <= 3 ? car_x : 3;
        
        break;
    case GLUT_KEY_UP:
        car_z -= speed_car; // Move forward
        if (collideWithBarrierZ())
        {
			car_z += speed_car;
		}
        break;
    case GLUT_KEY_DOWN:
        car_z += speed_car; // Move backward
        if (collideWithBarrierZ())
        {
            car_z -= speed_car;
        }
        break;
    }
    if (isFirst) {
		camera = Camera(Vector3f(car_x, car_y + 2, car_z+1.5), Vector3f(car_x, car_y, car_z - 5), Vector3f(0, 1, 0));
	}
    else
    {
        camera = Camera(Vector3f(0, car_y + 3, car_z + 5), Vector3f(0, car_y, car_z - 5), Vector3f(0, 1, 0));
    }
}

float euclideanDistance(float x1, float y1, float z1, float x2, float y2, float z2) {
    float distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2) + pow((z2 - z1), 2));
    /*printf("Distance: %f\n", distance);*/
    return distance;
}
void collideWithCoins(int* score) {
    for (int i = 0; i < 5; i++) {
        //printf("Coin %d: %d\n", i, coin_collected[i]);
        float dist = euclideanDistance(car_x, car_y, car_z, coin_coords[i][0], coin_coords[i][1], coin_coords[i][2]);
        if (dist < 2 && car_x== coin_coords[i][0] && !coin_collected[i]) {
			(*score)++;
            coin_collected[i] = true;
        }
    }

}

bool collideWithBarrierZ() {
    for (int i = 0; i < 5; i++) {
		float dist = euclideanDistance(car_x, car_y, car_z, barrier_coords[i][0], barrier_coords[i][1], barrier_coords[i][2]);
        //printf("Barrier %d: %f\n", i, dist);
        if (dist < 2 && car_x == barrier_coords[i][0]) {
			return true;
		}
	}
    return false;

}

bool collideWithBarrierX() {
    for (int i = 0; i < 5; i++) {
        float dist = euclideanDistance(car_x, car_y, car_z, barrier_coords[i][0], barrier_coords[i][1], barrier_coords[i][2]);
        //printf("Barrier %d: %f\n", i, dist);
        if (dist < 1.41) { //1.414214
            return true;
        }
    }
    return false;

}