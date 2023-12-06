// Door.cpp
#include "Door.h"
#include <iostream>
#include "Model_3DS.h"
#include "glut.h"

 int openDoor = 0;
 int openDoorAngle = 0;
Model_3DS model_door;
void renderDoor() {
	glPushMatrix();


	glTranslatef(-1.8, 3, -210);  //constant
	glScaled(0.35, 0.35, 0.35);
	glTranslated(-openDoor, 0, 0);
	glRotated(openDoorAngle, 0, 1, 0);
	glRotatef(180, 0, 1, 0);
	model_door.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.8, 3, -210);  //constant
	glScaled(0.35, 0.35, 0.35);
	glTranslated(openDoor, 0, 0);
	glRotated(-openDoorAngle, 0, 1, 0);
	model_door.Draw();
	glPopMatrix();

}

void  loadDoorTexture()
{
	model_door.Load("Models/door/door1.3ds");

}


