#ifndef GLASS_H
#define GLASS_H

#include "point.h"
#include "colors.h"
#include "math.h"

class Glass : public Drawable {
	void drawSide(Point one, Point two, Point three, Point four) {
		Point normal = (two - one).cross(three - one).unitVector();
		glBegin(GL_TRIANGLES); {
			glColor4f(green.r, green.g, green.b, alpha);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(one.x, one.y, one.z);
			glVertex3f(two.x, two.y, two.z);
			glVertex3f(three.x, three.y, three.z);

			glVertex3f(three.x, three.y, three.z);
			glVertex3f(four.x, four.y, four.z);
			glVertex3f(one.x, one.y, one.z);
		} glEnd();
	}
	bool invert = false;
	float anim_time = 5;
	float time_elapsed = 0;
	float alpha;
	bool broken;
	float glass_dist = 0;
	public:
	void brake() {
		broken = true;
	}

	void render_glass(float time) {
			time_elapsed += time;
			if(time_elapsed > anim_time) {
				time_elapsed -= anim_time;
				invert = !invert;
			}
			alpha = time_elapsed / anim_time;
			if(invert) {
				alpha = 1 - alpha;
			}
			float depth = .2;
			Point points[]  = {
				Point(-1, 1, 0),
				Point(-1, -1, 0),
				Point(1, -1, 0),
				Point(1, 1, 0),
				Point(-1, 1, depth),
				Point(-1, -1, depth),
				Point(1, -1, depth),
				Point(1, 1, depth)
				};

			glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
			drawSide(points[0], points[1], points[2], points[3]);
			drawSide(points[4], points[5], points[6], points[7]);

			//top
			drawSide(points[4], points[7], points[3], points[0]);
			//left
			drawSide(points[4], points[5], points[1], points[0]);
			//right
			drawSide(points[7], points[6], points[2], points[3]);
			//bottom
			drawSide(points[5], points[1], points[2], points[6]);
		}

	void render(GLfloat time) {
		if(broken) {
			glass_dist += time * 10;
			glPushMatrix();
				glScalef(.5, .5, 1);
				glTranslatef(glass_dist, glass_dist, 0);
				render_glass(time);
			glPopMatrix();
			glPushMatrix();
				glScalef(.5, .5, 1);
				glTranslatef(-glass_dist, glass_dist, 0);
				render_glass(time);
			glPopMatrix();
			glPushMatrix();
				glScalef(.5, .5, 1);
				glTranslatef(glass_dist, -glass_dist, 0);
				render_glass(time);
			glPopMatrix();
			glPushMatrix();
				glScalef(.5, .5, 1);
				glTranslatef(-glass_dist, -glass_dist, 0);
				render_glass(time);
			glPopMatrix();
		} else {
			render_glass(time);
		}
	}
};

#endif

