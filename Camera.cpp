#include "Camera.h"
#include <stdio.h>
#include <glut.h>
#include <math.h>
#define DEG2RAD(a) (a * 0.0174532925)

// Implement constructors
Camera::Camera(float eyeX, float eyeY, float eyeZ,
	float centerX, float centerY, float centerZ,
	float upX, float upY, float upZ) {
	eye = Vector3f(eyeX, eyeY, eyeZ);
	center = Vector3f(centerX, centerY, centerZ);
	up = Vector3f(upX, upY, upZ);
}

Camera::Camera(Vector3f Eye, Vector3f Centre, Vector3f Up) {
	eye = Vector3f(Eye.x, Eye.y, Eye.z);
	center = Vector3f(Centre.x, Centre.y, Centre.z);
	up = Vector3f(Up.x, Up.y, Up.z);
}

// Implement other member functions
void Camera::moveX(float d) {
	Vector3f right = up.cross(center - eye).unit();
	eye = eye + right * d;
	center = center + right * d;
}

void Camera::moveY(float d) {
	eye = eye + up.unit() * d;
	center = center + up.unit() * d;
}

void Camera::moveZ(float d) {
	Vector3f view = (center - eye).unit();
	eye = eye + view * d;
	center = center + view * d;
}

void Camera::rotateX(float a) {
	Vector3f view = (center - eye).unit();
	Vector3f right = up.cross(view).unit();
	view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
	up = view.cross(right);
	center = eye + view;
}

void Camera::rotateY(float a) {
	Vector3f view = (center - eye).unit();
	Vector3f right = up.cross(view).unit();
	view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
	right = view.cross(up);
	center = eye + view;
}

void Camera::look() {
	gluLookAt(
		eye.x, eye.y, eye.z,
		center.x, center.y, center.z,
		up.x, up.y, up.z
	);
}
