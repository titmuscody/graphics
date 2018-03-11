

#ifndef POINT_H
#define POINT_H

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
};

#endif
