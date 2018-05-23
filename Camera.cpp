#include "Camera.h"

//************************************
// Method:    Camera
// FullName:  Camera::Camera
// Access:    public 
// Initializes the camera. focal takes place for "at" point on Angel.h
//************************************
Camera::Camera() {
	this->focal = vec4(0, 0, 0, 1);
	this->position = vec4(0, 0, 20, 1);
	this->up = vec4(0, 1, 0, 0);
	this->view = LookAt(position, focal, up);
}

void Camera::rotateZ(GLdouble d) {

}

//************************************
// Method:    update
// FullName:  Camera::update
// Access:    public 
// Returns:   void
// Updates components of camera. Also adds some camera shake with respect to linear velocity of attached ship.
//************************************
void Camera::update() {
	this->view = LookAt(position, focal, up);
}