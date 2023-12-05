// Car.cpp

#include "Barrier.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_barrier;
float barrier_coords[5][3] = {
        {-2, 0, -5},
        {-1, 0, -20},
        {0, 0, -35},
        {1, 0, -50},
        {2, 0, -80}
};

void loadBarrier() {
    model_barrier.Load("Models/concrete_barrier/Concrete_Barricade.3ds");
}

void renderBarrier(float translate_x, float translate_y, float translate_z) {
    glPushMatrix();  
    //-2 0 -5
    glTranslatef(translate_x,translate_y,translate_z);
    glRotated(90, 0, 1, 0);
    glScaled(0.5, 0.5, 0.5);
    model_barrier.Draw();
    glPopMatrix();
}

void renderBarriers() {
    for (int i = 0; i < 5; i++) {
		renderBarrier(barrier_coords[i][0], barrier_coords[i][1], barrier_coords[i][2]);
	}
}
