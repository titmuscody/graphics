#ifndef PYRAMID_H
#define PYRAMID_H

#include "point.h"
#include "colors.h"
#include "math.h"

class Pyramid : public Drawable {
	void drawSide(Point one, Point two, Point three) {
		GLfloat steps = 9;
		Point vertStep = (1 / steps) * (one - two);
		Point oppVertStep = (1 / steps) * (one - three);

		Point i = two;
		Point oppi = three;
		while(i != one) {
			Point inext = i + vertStep;
			Point oppinext = oppi + oppVertStep;

			Point cur = i;
			Point next = inext;
			Point horDir = (1 / steps) * (oppi - i);
			Point nextHorDir = (1 / steps) * (oppinext - inext);
			while(cur != oppi || next != oppinext) {
				Point curNext = cur + horDir;
				Point nextNext = next + nextHorDir;
				drawSingleTriangle(cur, curNext, next);
				drawSingleTriangle(curNext, nextNext, next);
				cur = cur + horDir;
				next = next + nextHorDir;
			}
			i = i + vertStep;
			oppi = oppi + oppVertStep;
		}
	}
	void drawSingleTriangle(Point one, Point two, Point three) {
		Point orig_normal = (two - one).cross(three - one).unitVector();
		Point normal;
		glBegin(GL_TRIANGLES); {
			vertexColor(red);
			normal = 7 * orig_normal;
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(one.x, one.y, one.z);
			normal = 5 * orig_normal;
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(two.x, two.y, two.z);
			normal = 2 * orig_normal;
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(three.x, three.y, three.z);
		} glEnd();
	}
	/*
	float getHeight(float x, float y) {
		printf("pos is %ix%i\n", x, y);
		unsigned int row = (int)((y + 1) / 2) * 4;
		unsigned int col = (int)((x + 1) / 2) * 4 * 2048;
		GLfloat height = 0;
		printf("pos is %ix%i\n", row, col);
		height = *(bumpFile + row + col) + *(bumpFile + row + col + 1) + *(bumpFile + row + col + 2);
		//printf("height is %f\n", height);
		if(height > .1) {
			height /= (3 * 255);
		}
		printf("height is %f\n", height);
		return height * 18;
	}
	unsigned char* bumpFile;
	*/

	void drawBottom(Point one, Point two, Point three, Point four) {
		Point normal = (two - one).cross(three - one).unitVector();
		glBegin(GL_TRIANGLES); {
			vertexColor(red);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(one.x, one.y, one.z);
			glVertex3f(two.x, two.y, two.z);
			glVertex3f(three.x, three.y, three.z);

			glVertex3f(three.x, three.y, three.z);
			glVertex3f(four.x, four.y, four.z);
			glVertex3f(one.x, one.y, one.z);
		} glEnd();
	}
	public:
	Pyramid() {
		/*
    FILE *rawFile;
		int width = 2048;
		int height = 2048;
    rawFile = fopen("tan-painted-wall-texture-crop.hgt", "rb");            // Open the .raw file r=read b=binary
    if (rawFile == NULL) {
      printf("Error problem reading tan wall\n");
      return;
    }

    long size = width*height*4;              // 4 bytes per bit RGBA
    bumpFile = (unsigned char*) malloc(size+10); // allocate space for the file in
                                             // memory, not sure why +10
                                             // found as an example 

    long cnt = fread(bumpFile, 1, size, rawFile); // Read into bits
                                              // size number of bytes (1=bytes)
                                              // from rawFile 

    fclose(rawFile);                          // Close the File when done
  
    if (cnt != size)                          // Check that we got the bytes
      printf("Not enough bits %d\n", cnt);    // asked for
		*/
	}

	void render(GLfloat time) {
		Point points[]  = {Point(-1, 1, 0), Point(-1, -1, 0), Point(1, -1, 0), Point(1, 1, 0), Point(0, 0, 1)};

		glEnable(GL_COLOR_MATERIAL);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		drawSide(points[4], points[3], points[0]);
		drawSide(points[4], points[2], points[3]);
		drawSide(points[4], points[1], points[2]);
		drawSide(points[4], points[0], points[1]);

		drawBottom(points[0], points[1], points[2], points[3]);
	}
};

#endif

