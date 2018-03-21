

#ifndef POINT_H
#define POINT_H

#include "math.h"

class Point {
    public:
    float x;
    float y;
    float z;
    Point() {
        x = 0;
        y = 0;
        z = 0;
    }
    Point(float nx, float ny, float nz) {
        x = nx;
        y = ny;
        z = nz;
    }
		friend bool operator==(Point lhs, const Point& rhs) {
			float thresh = .0001;
			return abs(lhs.x - rhs.x) < thresh && abs(lhs.y - rhs.y) < thresh && abs(lhs.z - rhs.z) < thresh;
		}
		friend bool operator!=(Point lhs, const Point& rhs) {
			return !(lhs == rhs);
		}
    friend Point operator+(Point lhs, const Point& rhs) {
        return Point(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }
    friend Point operator-(Point lhs, const Point& rhs) {
        return Point(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }
    friend Point operator*(float mul, const Point& rhs) {
        return Point(rhs.x*mul, rhs.y*mul, rhs.z*mul);
    }
    float size() {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    Point unitVector() {
        float mag = size();
				Point p;
				if(mag == 0) {
					return Point(0, 0, 0);
				}
        return Point(x / mag, y / mag, z / mag);
    }
		Point cross(Point r) {
			Point res;
			res.x = y * r.z - r.y * z;
			res.y = r.x * z - x * r.z;
			res.z = x * r.y - r.x * y;
			return res;
		}
		static Point normal(Point one, Point two, Point three) {
			Point res = (one - two).cross(two - three);
			return res.unitVector();
		}
		static GLfloat dot(Point one, Point two) {
			return one.x * two.x + one.y * two.y + one.z * two.z;
		}
};

#endif
