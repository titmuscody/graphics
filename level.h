#ifndef LEVEL_H
#define LEVEL_H

#include <algorithm>

#include "point.h"
#include "colors.h"
#include "math.h"

#include "ball.h"

const int SIZE = 64;

class Level : public Drawable {
	void drawSide(Point one, Point two, Point three, Point four) {

		glEnable(GL_COLOR_MATERIAL);

		glBegin(GL_TRIANGLES); {
			Color color;
			float height = one.y + two.y + three.y + four.y;
			height /= 4;
			if(height < 0) {
				color = red;
			} else if(height < 0.4) {
				color = blue;
			} else if(height < 0.5) {
				color = green;
			} else if(height < 0.65) {
				color = brown;
			} else if(height < 1) {
				color = white;
			} else {
				color = red;
			}
			glColor3f(color.r, color.g, color.b);

			Point normal = (two - one).cross(three - one).unitVector();
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(one.x, one.y, one.z);
			glVertex3f(two.x, two.y, two.z);
			glVertex3f(three.x, three.y, three.z);

			normal = (one - three).cross(four - three).unitVector();
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(three.x, three.y, three.z);
			glVertex3f(four.x, four.y, four.z);
			glVertex3f(one.x, one.y, one.z);
		} glEnd();
		/*
		glPushMatrix();
		glBegin(GL_LINES); {
			glColor3f(red.r, red.g, red.b);

			Point normal = (two - one).cross(three - one).unitVector();
			Point start = one;
			Point end = one + (1 / scale) * normal;
			glVertex3f(start.x, start.y, start.z);
			glVertex3f(end.x, end.y, end.z);
		} glEnd();
		glPopMatrix();
		*/
	}
	float lvl[SIZE][SIZE];
	float rough;
	float rmin;
	float rmax;
	float scale = 80;
	public:
	Level() {
		for(int i = 0; i < SIZE; ++i) {
			for(int j = 0; j < SIZE; ++j) {
				lvl[i][j] = -0.0f;
			}
		}
		rough = .9;
		rmin = -.05;
		rmax = .75;
		createLevel();
	}
	float get_random() {
		float scale = rand() / (float) RAND_MAX;
		float number = rmin + scale * (rmax - rmin);
		//adjust range
		float dist = rmax - rmin;
		dist *= rough;
		rmax = rmin + dist;
		return number;
	}

	void add_gauss_filter() {
		for(int row = 0; row < SIZE; ++row) {
			for(int col = 0; col < SIZE; ++col) {
				// horizontal gaussian filter
				float total = 0;
				total += getVal(row-2, col) * .026f;
				total += getVal(row-1, col) * .237f;
				total += getVal(row, col) * .47f;
				total += getVal(row+1, col) * .237f;
				total += getVal(row+2, col) * .026f;
				lvl[row][col] = total;

				// vertical gaussian filter
				total = 0;
				total += getVal(row, col-2) * .026f;
				total += getVal(row, col-1) * .237f;
				total += getVal(row, col) * .47f;
				total += getVal(row, col+1) * .237f;
				total += getVal(row, col+2) * .026f;
				lvl[row][col] = total;
			}
		}
	}
	void add_mean_filter() {
		for(int row = 0; row < SIZE; ++row) {
			for(int col = 0; col < SIZE; ++col) {
				// horizontal gaussian filter
				float total = 0;
				for(int i = -1; i < 2; i++) {
					for(int j = -1; j < 2; j++) {
						total += getVal(row + i, col + j) / 9;
					}
				}
				lvl[row][col] = total;
			}
		}
	}
	void createLevel() {
		// set outside points
		lvl[0][0] = 1.0f;
		lvl[SIZE-1][0] = 1.0f;
		lvl[0][SIZE-1] = 1.0f;
		lvl[SIZE-1][SIZE-1] = 1.0f;


		// run diamond square stuff
		square(0, SIZE-1, 0, SIZE-1);

		// smooth the surface
		int gauss_count = 1;
		for(int i = 0; i < gauss_count; ++i) {
			add_gauss_filter();
		}
		int mean_count = 0;
		for(int i = 0; i < mean_count; ++i) {
			add_mean_filter();
		}
	}

	float getVal(int row, int col) {
		if(row < 0) {
			row = 0;
		}
		if(row >= SIZE) {
			row = SIZE - 1;
		}
		if(col < 0) {
			col = 0;
		}
		if(col >= SIZE) {
			col = SIZE - 1;
		}
		return lvl[row][col];
	}

	void square(int left, int right, int top, int bottom) {
		int diff = right - left;
		if(diff <= 1)
			return;
		int midrow = top + (diff / 2);
		int midcol = left + (diff / 2);
		float height = lvl[top][left] + lvl[bottom][left] + lvl[bottom][right] + lvl[top][right];
		height *= .25f;
		lvl[midrow][midcol] = height + get_random();

		lvl[midrow][left] = (lvl[top][left] + lvl[bottom][left] + lvl[midrow][midcol] + getVal(midrow, midcol - diff)) * .25 + get_random();
		lvl[bottom][midcol] = (lvl[bottom][left] + lvl[bottom][right] + lvl[midrow][midcol] + getVal(midrow + diff, midcol)) * .25 + get_random();
		lvl[midrow][right] = (lvl[top][right] + lvl[bottom][right] + lvl[midrow][midcol] + getVal(midrow, midcol + diff)) * .25 + get_random();
		lvl[top][midcol] = (lvl[top][left] + lvl[top][right] + lvl[bottom][midcol] + getVal(midrow - diff, midcol)) * .25 + get_random();

		square(left, midcol, top, midrow);
		square(left, midcol, midrow, bottom);
		square(midcol, right, midrow, bottom);
		square(midcol, right, top, midrow);
	}

	void render(GLfloat time) {
		
		glEnable(GL_COLOR_MATERIAL);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		glPushMatrix();
		glScalef(scale, scale, scale);

		for(float row = 0, row2 = 1; row2 < SIZE; ++row, ++row2) {
			for(float col = 0, col2 = 1; int(col2) < SIZE; ++col, ++col2) {
				// reversing y directino so it follows the arrays itreation better
				Point one = Point(col / SIZE, lvl[int(row)][int(col)], (row / SIZE));
				Point two = Point(col / SIZE, lvl[int(row2)][int(col)], (row2 / SIZE));
				Point three = Point((col2) / SIZE, lvl[int(row2)][int(col2)], (row2 / SIZE));
				Point four = Point((col2) / SIZE, lvl[int(row)][int(col2)], (row / SIZE));
				one = one + Point(-0.5, 0, -0.5);
				two = two + Point(-0.5, 0, -0.5);
				three = three + Point(-0.5, 0, -0.5);
				four = four + Point(-0.5, 0, -0.5);
				drawSide(one, two, three, four);
			}
		}
		glPopMatrix();
	}

	void touching(Ball *ball) {
		vector<Point> points;
		Point the_norm;
		Point pos;
		bool process = false;
		float small_dist = ball->radius;
		for(float i = 0; i < SIZE; ++i) {
			for(float j = 0; j < SIZE; ++j) {
				Point p = Point(i / SIZE, lvl[int(j)][int(i)], j / SIZE);
				p = scale * p;
 				p = p + (scale * Point(-0.5, 0, -0.5));
				float dist = (p - ball->pos).size();
				Point two = Point((i + 1) / SIZE, lvl[int(j)][int(i+1)], j / SIZE);
				two = scale * two;
				two = two + (scale * Point(-0.5, 0, -0.5));
				Point four = Point(i / SIZE, lvl[int(j+1)][int(i)], (j + 1) / SIZE);
				four = scale * four;
				four = four + (scale * Point(-0.5, 0, -0.5));
				Point norm = (four - p).cross(two - p).unitVector();
				//printf("angle %f\n", acos(Point::dot(norm, vel) / (norm.size() * vel.size())));
				float angle = acos(Point::dot(-1 * ball->vel, norm) / (ball->vel.size() * norm.size()));
				if(dist < small_dist) {
					if(i != float(SIZE - 1) && j != float(SIZE - 1)) {
						/*
						printf("two %f %f %f four %f %f %f p %f %f %f\n", 
							two.x, two.y, two.z, 
							four.x, four.y, four.z,
							p.x, p.y, p.z);
						*/
						points.push_back(p);
						the_norm = norm;
						pos = p;
						//printf("norm %f %f %f, %f and %f\n", norm.x, norm.y, norm.z, dist, angle);
						process = true;
					}
				}
			}
		}
		while(points.size() > 0) {
			for(auto begin = points.begin(); begin != points.end();) {
				if((*begin - ball->pos).size() > ball->radius) {
					begin = points.erase(begin);
				} else {
					begin++;
				}
			}
			ball->pos = ball->pos + Point(0, .1, 0);
			//printf("moving ball count=%i, pos=%f\n", points.size(), ball->pos.y);
		}
		if(process) {
			ball->bounce(pos, the_norm);
		}
	}
};

#endif

