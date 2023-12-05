// Car.cpp

#include "Star.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_star;
bool star_collected[5] = {false, false, false, false, false};
float star_coords[5][3] = {
    {-1.0f, 0.45f, -220.0f}, 
    {1.0f, 0.45f, -230.0f},
    {1.0f, 0.45f, -240.0f},
    {-2.0f,0.45f, -250.0f},
    {2.0f, 0.45f, -250.0f}
};

void loadStar() {
    model_star.Load("Models/star/star.3ds");
}

void renderStar(float translate_x, float translate_y, float translate_z) {
    glPushMatrix();    
    glTranslatef(translate_x,translate_y,translate_z);
    glRotated(90, 0, 1, 0);
    glRotated(90, 0, 0, 1);
    glScaled(0.3, 0.3, 0.3);
    model_star.Draw();
    glPopMatrix();
}

void renderStars() {
    for (int i = 0; i < 5; i++) {
        if (!star_collected[i]) {
			renderStar(star_coords[i][0], star_coords[i][1], star_coords[i][2]);
		}
	}
}
