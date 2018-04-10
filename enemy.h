#ifndef ENEMY_H
#define ENEMY_H

#include "math.h"

#include "colors.h"
#include "wall.h"

using std::vector;

class Enemy: public Drawable {
	public:
		void render(float time) override {
			glPushMatrix();
				//glTranslatef(loc.x, loc.y, loc.z);
				//glRotatef(rot, rotPoint.x, rotPoint.y, rotPoint.z);
				vertexColor(orange);
				glutSolidSphere(radius, 20, 20);
			glPopMatrix();
    }
		void move() override {
			//Point dest = loc + (speed * dir);
			//lookat(dest);
			//setPos(dest);
		}
		Point loc;
		float radius = 15;
	private:
		void lookat(Point here) {
			/*
			Point looking = (here - loc).unitVector();
			Point start = Point(0, 0, 1);
			rotPoint = start.cross(looking);
			rot = (180 / M_PI) * acos(Point::dot(start, looking));
			*/
		}
		void setPos(Point here) {
			loc = here;
		}
};
#endif
