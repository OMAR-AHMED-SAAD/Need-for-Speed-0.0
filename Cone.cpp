// Car.cpp

#include "Cone.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_cone;
float cone_coords[5][3] = {
    {1.0f, 0.4f, -220.0f},
    {-1.0f, 0.4f, -230.0f},
    {-1.0f, 0.4f, -240.0f},
    {2.0f,0.4f, -260.0f},
    {-2.0f, 0.4f, -260.0f}
};

void loadCone() {
    model_cone.Load("Models/cone/cone.3ds");
}

void renderCone(float translate_x, float translate_y, float translate_z) {
    glPushMatrix();    
    glTranslatef(translate_x,translate_y,translate_z);
    glRotated(90, 0, 1, 0);
    glScaled(0.3, 0.3, 0.3);
    model_cone.Draw();
    glPopMatrix();
}

void renderCones() {
    for (int i = 0; i < 5; i++) {
		renderCone(cone_coords[i][0], cone_coords[i][1], cone_coords[i][2]);
	}
}