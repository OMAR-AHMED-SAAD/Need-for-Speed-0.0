#include "Road.h"
#include "Model_3DS.h"
#include "glut.h"

Model_3DS model_road;

void loadRoad() {
    model_road.Load("Models/Road/HwRoad.3ds");
}

void renderRoad(int roadBlocksNum) {
	for (int i = -roadBlocksNum/2; i <= roadBlocksNum/2; i += 2) {
	// Draw road Model
	glPushMatrix();
	glTranslatef(0, 0, i*5);
	glScalef(0.5, 0.5, 0.5);
	model_road.Draw();
	glPopMatrix();
	}
}
