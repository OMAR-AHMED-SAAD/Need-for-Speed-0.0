#include "Road.h"
#include "Model_3DS.h"
#include "glut.h"
#include "car.h"
Model_3DS model_road;
Model_3DS model_road2;

void loadRoad() {
	model_road.Load("Models/Road/HwRoad.3ds");
	model_road2.Load("Models/Road2/HwRoad.3ds");
}

void renderRoad(int roadBlocksNum) {
	if (level2) {
		for (int i = -roadBlocksNum / 2; i <= roadBlocksNum / 2; i += 2) {
			// Draw road Model
			glPushMatrix();
			glTranslatef(0, 0, i * 5);
			glScalef(0.5, 0.5, 0.5);
			model_road2.Draw();
			glPopMatrix();
		}
		return;
	}
	for (int i = -roadBlocksNum/2; i <= roadBlocksNum/2; i += 2) {
	// Draw road Model
	glPushMatrix();
	glTranslatef(0, 0, i*5);
	glScalef(0.5, 0.5, 0.5);
	model_road.Draw();
	glPopMatrix();
	}
}
