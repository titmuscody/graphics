
#ifndef SPIRAL_H
#define SPIRAL_H

#include "point.h"
#include "math.h"

class Spiral : public Mover {
	const GLfloat E = 2.71828182845904523536;
	float anim_time;
	float time_passed = 0;
	public:
	Spiral(float max_time) {
		anim_time = max_time;
	}

	Point get_position(GLfloat time) {
		time_passed += time;
		if(time_passed > anim_time) {
			time_passed -= anim_time;
		}
		GLfloat theta = time_passed;
		GLfloat xrad = 20.0;
		GLfloat yrad = 5.0;
		GLfloat zrad = 15.0;
		GLfloat k = .5;
		GLfloat w = 5;
		GLfloat x = xrad * pow(E, -k*theta) * cos(w * theta);
		GLfloat y = yrad * theta;
		GLfloat z = zrad * pow(E, -k*theta) * sin(w * theta);
		return Point(x, y, z);
	}
};

#endif

