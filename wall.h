#ifndef WALL_H
#define WALL_H

#include "point.h"
#include "colors.h"
#include "math.h"

class Wall : public Drawable {
	void drawSide(Point one, Point two, Point three, Point four) {
		Point normal = (two - one).cross(three - one).unitVector();
		glPushMatrix();
		glTranslatef(loc.x, loc.y, loc.z);
		glRotatef(rot.x, 1, 0, 0);
		glRotatef(rot.y, 0, 1, 0);
		glScalef(scale.x, scale.y, scale.z);

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBegin(GL_TRIANGLES); {
			Color color = blue;
			float alpha = 0.5;
			glColor4f(color.r, color.g, color.b, alpha);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(one.x, one.y, one.z);
			glVertex3f(two.x, two.y, two.z);
			glVertex3f(three.x, three.y, three.z);

			glVertex3f(three.x, three.y, three.z);
			glVertex3f(four.x, four.y, four.z);
			glVertex3f(one.x, one.y, one.z);
		} glEnd();
		glPopMatrix();
	}
	Point scale;
	Point rot;
	public:
	Point dir;
	Point loc;
	Wall(Point position, Point rot, Point scale, Point direction) {
		loc = position;
		dir = direction;
		this->scale = scale;
		this->rot = rot;
	}

	void render(GLfloat time) {
		
		Point points[]  = {Point(-1, 1, 0), Point(-1, -1, 0), Point(1, -1, 0), Point(1, 1, 0)};

		glEnable(GL_COLOR_MATERIAL);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		drawSide(points[0], points[1], points[2], points[3]);
	}
};

#endif

