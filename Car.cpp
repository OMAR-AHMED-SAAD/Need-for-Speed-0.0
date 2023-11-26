// Car.cpp

#include "Car.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_car;
int car_x = 0;
int car_y = 0;
int car_z = 2;
int speed = 1;
void loadCar() {
    model_car.Load("Models/car/Crysler_new_yorker_1980.3ds");
}

void renderCar() {
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glScaled(0.5,0.5,0.5);
    glTranslatef(car_x, car_y, car_z);  
    model_car.Draw();
    glPopMatrix();
}

void moveCar(unsigned char key, int x, int y) {
    switch (key) {
    case 'j': case 'J':
        car_z -= speed; // Move left
        break;
    case 'l': case 'L':
        car_z += speed; // Move right
        break;
    case 'i': case 'I':
        car_x += speed; // Move forward
        break;
    case 'k': case 'K':
        car_x -= speed; // Move backward
        break;
    }

    // Optionally, add glutPostRedisplay() here if automatic redrawing is needed

}