#ifndef BALL_H
#define BALL_H

#include "math.h"

#include "colors.h"

class Ball: public Drawable {
    public:
		Point pos;
		Point vel;
		float radius;
		Ball() {
			pos = Point(0, 70, 0);
			vel = Point(0, 0, 0);
			radius = 3;
		}
    void render(float time) {
			glPushMatrix();
				vertexColor(red);
				glTranslatef(pos.x, pos.y, pos.z);
				glutSolidSphere(radius, 20, 16);
			glPopMatrix();
    }
		void add_vel(Point p) {
			vel = vel + p;
		}
		void bounce(Point mesh_pos, Point norm) {
			Point newPos = mesh_pos + (radius * (-1 * vel).unitVector());
			Point V = vel.unitVector();
			float angle = acos(Point::dot(-1 * V, norm));
			if(angle == 0) {
				vel = -.9 * vel;
			} else {
				Point tick = V.cross(norm).cross(V).unitVector();
				Point Z = cos(angle) * V + sin(angle) * tick;
				vel = .9 * Z;
				//vel = .5 * vel.size() * norm.unitVector();
			}
		}
		void update_position(float time) {
			pos = pos + vel;
		}
};

#endif
