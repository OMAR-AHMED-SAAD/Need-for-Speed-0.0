#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include "Vector3f.h"
#include "Camera.h"
#include "Scene.h"
#include "Car.h"
#include "Road.h"
#include "Cone.h"
#include "Star.h"
#include "Cup.h"
#include "Barrier.h"
#define GLUT_KEY_ESCAPE 27

//Window Size and title
int HEIGHT = 720;
int WIDTH = 1080;
char title[] = "Need for speed 0.0";


// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.01;
GLdouble zFar = 1000;

//Intial Camera Position
Vector3f Eye(20, 10, 20);
Vector3f At(0, 0, 0);
Vector3f Up(0, 1, 0);

Camera camera;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;



//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	camera = Camera(Eye, At, Up);
	camera.look();
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Update Camera	
//=======================================================================
void updateCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspectRatio, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

//=======================================================================
// Keyboard Function - Updated for Camera Control
//=======================================================================
void keyboard(unsigned char key, int x, int y) {
	float d = 1.0;

	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
		break;
	}
	moveCar(key, x, y);
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glutPostRedisplay();
}

//=======================================================================
// Special Function - Updated for Camera Control
//=======================================================================
void special(int key, int x, int y) {
	float a = 3.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}
	

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
int prevX = 0;
int prevY = 0;
void mouseMotion(int x, int y) {
	// Calculate the change in mouse position
	int deltaX = x - prevX;
	int deltaY = y - prevY;

	// Sensitivity factor for mouse movement
	float sensitivity = 0.1f;

	// Update the camera's orientation based on mouse movement
	camera.rotateY(deltaX * sensitivity);
	camera.rotateX(deltaY * sensitivity);

	// Update the previous mouse position
	prevX = x;
	prevY = y;

	// Redisplay the scene
	glutPostRedisplay();
}

//=======================================================================
// Mouse Function
//=======================================================================
void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		// Store the initial mouse position when a button is pressed
		prevX = x;
		prevY = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void reshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}
//  a callback function commonly used in OpenGL applications to handle window resizing.
//  Its purpose is to adjust the viewport and projection matrix to match the new dimensions of the window 
// and maintain the correct aspect ratio for rendering.

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets() {
	// Loading Model files
	//model_house.Load("Models/star/star.3ds");
	loadCar();
	loadRoad();
	loadCone();
	loadStar();
	loadCup();
	loadBarrier();
	// Loading texture files
	loadSceneTextures();
}
void drawAxes(float length) {
	glBegin(GL_LINES);

	// X axis in red
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(length, 0.0, 0.0);

	// Y axis in green
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, length, 0.0);

	// Z axis in blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, length);

	glEnd();
}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	updateCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	////drawScene();
	renderRoad(240);

	renderCar();
	//renderCone();
	//renderStar();
	//renderCup();
	//renderBarrier();
	//draw point at the origin
	drawAxes(30);
glPointSize(5);
glColor3f(1,0, 0);
glBegin(GL_POINTS);
glVertex3f(0, 0, 0);
glEnd();

//draw line to measure car length
//glLineWidth(5);
//glColor3f(1, 0, 0);
//glBegin(GL_LINES);
//glVertex3f(0, 0, -1);
//glVertex3f(0, 0, -3);
//glEnd();


glColor3f(1, 1, 1);
		
		renderSkyBox();

	//// Draw house Model
	//glPushMatrix();
	//glRotatef(90.f, 1, 0, 0);
	//model_house.Draw();
	//glPopMatrix();

	glutSwapBuffers();
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(keyboard);

	glutSpecialFunc(special);

	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);

	glutReshapeFunc(reshape);

	init();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}