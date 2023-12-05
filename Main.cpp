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
#include "Coin.h"
#define GLUT_KEY_ESCAPE 27

//Window Size and title
int HEIGHT = 720;
int WIDTH = 1080;
char title[] = "Need for speed 0.0";

// Instance Variable
int score = 0;

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
bool isFirst = false;
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
	case 'i':
		camera.rotateX(d);
		break;
	case 'k':
		camera.rotateX(-d);
		break;
	case 'j':
		camera.rotateY(d);
		break;
	case 'l':
		camera.rotateY(-d);
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
		break;
	}
	
	/*GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);*/
	glutPostRedisplay();
}

//=======================================================================
// Special Function - Updated for Camera Control
//=======================================================================
void special(int key, int x, int y) {	
	moveCar(key, camera, isFirst);
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
		isFirst = true;
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
		isFirst = false;
	
	moveCar(NULL, camera, isFirst);
	glutPostRedisplay();
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
	loadCoin();
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

void print(){
	glPushAttrib(GL_CURRENT_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	char scoreString[20];
	sprintf(scoreString, "Score: %d", score);
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2i(720, 580);
	for (char* c = scoreString; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	updateCamera();
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
	renderBarrier();
	renderCoin();
	//draw point at the origin
	drawAxes(30);
	glColor3f(1, 1, 1);
	renderSkyBox();
	print();
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
	//glutMotionFunc(mouseMotion);

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
