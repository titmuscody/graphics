


class Point {
    public:
    float x;
    float y;
    float z;
    Point() {
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
};
