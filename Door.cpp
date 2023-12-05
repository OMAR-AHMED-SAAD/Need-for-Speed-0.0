// Door.cpp

#include "Door.h"
#include "glut.h"


void renderDoor() {
    
    glPushMatrix();
    //glColor3b(0.5, 0.5, 0.5);
    glTranslatef(0.0f, 1.5f, -210.0f);
    glRotated(90, 0, 0, 1);
    glScaled(0.2, 0.2, 0.2);

    glBegin(GL_QUADS); 
    glVertex3f(-1.0f, -1.5f, 0.0f); // Bottom Left
    glVertex3f(1.0f, -1.5f, 0.0f);  // Bottom Right
    glVertex3f(1.0f, 1.5f, 0.0f);   // Top Right
    glVertex3f(-1.0f, 1.5f, 0.0f);  // Top Left
    glEnd(); 
    
    glPopMatrix();
}
