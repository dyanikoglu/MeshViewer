#pragma once
#include "Angel/Angel.h"

class Camera {
public:
	Camera();
	void update();
	mat4 view;
	vec4 position;
	vec4 focal; // at
	void rotateZ(GLdouble d);
private:
	vec4 up;
};