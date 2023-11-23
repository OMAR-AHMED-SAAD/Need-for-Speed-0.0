// Car.cpp

#include "Car.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_car;

void loadCar() {
    model_car.Load("Models/car/Crysler_new_yorker_1980.3ds");
}

void renderCar() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(0.1, 0.1, 0.1);
    model_car.Draw();
    glPopMatrix();
}
