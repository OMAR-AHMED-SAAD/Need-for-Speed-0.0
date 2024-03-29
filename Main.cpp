#include <Windows.h>
#include <mmsystem.h>
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
#include "Door.h"
#include "Human.h";
#include <cmath>
#include <string>
#pragma comment(lib, "winmm.lib")
#define GLUT_KEY_ESCAPE 27
// Define M_PI if it's not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
//Window Size and title
int HEIGHT = 720;
int WIDTH = 1080;
char title[] = "Need for speed 0.0";

// Instance Variable
int score = 0;
GameState currentGameState = START;
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

int remainingTime = 10;

void updateTimer(int value) {
	if (remainingTime > 0) {
		remainingTime -= 1; // Decrement the remaining time by one second
	}
	else {
		remainingTime = 10;
	}
	glutPostRedisplay();
	glutTimerFunc(1000, updateTimer, 0); 
}
void showStartScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Disable depth test to ensure the win screen appears on top
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	// Initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	char* rules = "You need to collect at least 1 coin to go to level 2. Otherwise, you LOSE!!";

	// Display the text
	glColor3f(1.0, 1.0, 0.0); // Yellow text color
	int textWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)rules);
	glRasterPos2i(WIDTH / 2 - textWidth / 2, HEIGHT / 2);
	for (const char* c = rules; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	char* goToLevel1 = "Press b to continue.";
	glColor3f(1.0, 1.0, 0.0); // Yellow text color
	textWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)goToLevel1);
	glRasterPos2i(WIDTH / 2 - textWidth / 2, HEIGHT / 2-50);
	for (const char* c = goToLevel1; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);

}
void showWinScreen() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Disable depth test to ensure the win screen appears on top
	glDisable(GL_DEPTH_TEST);

	
	glClearColor(0.537f, 0.812f, 0.941f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); 

	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	// Initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	
	std::string winText = "Congratulations! You Win! Score: " + std::to_string(score);

	// Display the text
	glColor3f(1.0, 1.0, 0.0); // Yellow text color
	int textWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)winText.c_str());
	glRasterPos2i(WIDTH / 2 - textWidth / 2, HEIGHT / 2);
	for (const char* c = winText.c_str(); *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);

	// Swap the buffers to display the win screen
	//glutSwapBuffers();
}

void showLoseScreen() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Disable depth test to ensure the win screen appears on top
	glDisable(GL_DEPTH_TEST);


	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	// Initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	std::string loseText = human_collected ? "You Killed Don Raymond :0" : "You Lost! Score: " + std::to_string(score);
	//const char* loseText = "You Lost";
	glColor3f(1.0, 1.0, 0.0); // Yellow text color
	int textWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)loseText.c_str());
	glRasterPos2i(WIDTH / 2 - textWidth / 2, HEIGHT / 2);
	for (const char* c = loseText.c_str(); *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	if(human_collected){
	glColor3f(0,0,0);
	glLineWidth(8.0);
	glBegin(GL_LINES);
	glVertex2f(0, 580);
	glVertex2f(100, 720);
	glEnd();
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);

	// Swap the buffers to display the win screen
	//glutSwapBuffers();
}



//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource() {
	//print level2 value 
	//printf("level2: %d\n", level2);
	float ambientGreenIntensity = level2? 1.0 : 0.2;
	float ambientBlueIntensity = level2 ? 0.0 : 0.0;
	float ambientRedIntensity = level2 ? 0.5 : 0.0;

	
	GLfloat lmodel_ambient[] = { ambientRedIntensity,ambientGreenIntensity, ambientBlueIntensity, 1.0f }; // Ambient light for the entire scene
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	// Define Light source 0 diffuse light as red
	GLfloat l0Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Red diffuse light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);

	// Define Light source 0 ambient light as a subtle red
	GLfloat l0Ambient[] = { ambientRedIntensity,ambientGreenIntensity,ambientBlueIntensity, 1.0f }; // Subtle red ambient light
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);


	// Set light source 0 position in World Space (adjust as needed)
	GLfloat l0Position[] = { 0.0f, 800.0f, 0.0f, 0.0f }; // Position of the light
	glLightfv(GL_LIGHT0, GL_POSITION, l0Position);

	//increase red intensity
	GLfloat Intensity[] = { ambientRedIntensity,ambientGreenIntensity, ambientBlueIntensity, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Intensity);

	GLfloat l0Direction[] = { 0.0f, 0.0f, 0.0f }; // No direction for a point light
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);
}

void InitSpotLightSource() {
	// Define Light source 1 (Green high-intensity spotlight)
	GLfloat l1Diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f }; // Green diffuse light
	GLfloat l1Specular[] = { 0.0f, 0.0f, 1.0f, 1.0f }; // Green specular light
	
	GLfloat l1Position[] = { car_x, 3.0f, car_z, 1.0f }; // Position at (car_x, 2.0, car_z)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1Specular);
	glLightfv(GL_LIGHT1, GL_POSITION, l1Position);

	GLfloat l1Intensity[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1Intensity);

	// Set spotlight properties for Light source 1 (GL_LIGHT1)
	GLfloat spotDirection[] = { 0.0f, -1.0f, -1.0f }; // Spotlight direction (pointing downwards)
	GLfloat spotExponent = 30.0f; // Adjust spotlight exponent for intensity
	GLfloat spotCutoff = 15.0f; // Set the cutoff angle to 25 degrees for a focused spotlight

	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
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
	InitLightSource();
	InitSpotLightSource();	

}

//=======================================================================
// Keyboard Function - Updated for Camera Control
//=======================================================================
bool isFirst = false;
void keyboard(unsigned char key, int x, int y) {
	float d = 1.0;
	switch(currentGameState) {
		case START:
			if(key == 'b')
				currentGameState = PLAYING;
			break;
		case PLAYING:
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
	}
	
	
	/*GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);*/
	glutPostRedisplay();
}

//=======================================================================
// Special Function - Updated for Camera Control
//=======================================================================
void special(int key, int x, int y) {
	if (currentGameState == PLAYING) {
		moveCar(key, camera, isFirst);
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
	if(currentGameState != PLAYING)
		return;
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
	loadDoorTexture();
	loadHuman();
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

void printScore(){
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
	glColor3f(0.0,1.0, 0.0);
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
	switch (currentGameState) {
		// Normal game rendering
	case START:
		showStartScreen();
		break;
	case PLAYING:
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

		renderRoad(120);
		renderCar();
		renderBarriers();
		collideWithCoins(&score);
		renderCoins();
		collideWithStars(&score);
		renderStars();
		renderCones();
		collideWithCup();
		renderCup();
		renderDoor();
		collidWithDoor(score);		

		collideWithHuman();
		renderHuman(remainingTime);
		
		//drawAxes(30);
		glColor3f(1, 1, 1);
		renderSkyBox();
		printScore();
		break;
	case WIN:
		showWinScreen();
		break;
	case LOSE:
		showLoseScreen(); 
		break;
	}
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

	glutTimerFunc(1000, updateTimer, 0);
	init();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	

	glutMainLoop();
}
