#include <GL/gl.h>

#include <math.h>
#include <vector>


#ifndef CAMERA_H
#define CAMERA_H


#include "colors.h"
#include "point.h"
#include "graphic.h"

using std::vector;

class Camera {

		Point vel;
    public:
		Point lookat;
		Point pos;
    Camera(Point orig) {
        pos = orig;
				vel = Point();
    }
		void add_vel(Point v) {
			vel = vel + v;
		}
    void update_position(float time) {
			pos = pos + vel;
			lookat = lookat + vel;
			vel = .1 * vel;
    }
    Point get_position() {
			return pos;
    }
		Point set_orientation(Point loc) {
			Point vec = (loc - pos).unitVector();
			lookat = pos + vec;
		}
    Point get_orientation() {
			return lookat;
    }
};
#endif
