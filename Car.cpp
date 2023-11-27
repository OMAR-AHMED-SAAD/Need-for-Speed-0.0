// Car.cpp
#include <iostream>
#include "Car.h"
#include "Model_3DS.h"
#include "glut.h"
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

void moveCar(unsigned char key, int x, int y, Camera& camera, bool isFirst) {
    switch (key) {
    case 'j': case 'J':
        car_x -= speed_car; // Move left
        break;
    case 'l': case 'L':
        car_x += speed_car; // Move right
        break;
    case 'i': case 'I':
        car_z -= speed_car; // Move forward
        break;
    case 'k': case 'K':
        car_z += speed_car; // Move backward
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