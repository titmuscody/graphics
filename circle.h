#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>

#include <math.h>
#include <vector>


#ifndef CIRCLE_H
#define CIRCLE_H


#include "colors.h"

using std::vector;

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

class Circle {
    vector<Point> points;
    vector<Point> destinations;

    public:
    Point loc;
    Circle() {
        int point_count = 15;
        float step = 2 * M_PI / point_count;
        for(int i = 0; i < point_count; ++i) {
            float angle = i * step;
            float x = cos(angle);
            float y = sin(angle);
            Point p = Point(x, y, 0.0);
            points.push_back(p);
        }
    }
     void render() {

        glPushMatrix();                             // Save Matrixes

//        glRotatef(rotation, 1.0, 0.0, 0.0);
        glTranslatef(loc.x, loc.y, 0.0);
        glScalef(0.25, 0.25, 0);

        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);

        glBegin(GL_POLYGON); {
        // draw hourglassish polygon
        vertexColor(green);
        for(int i = 0; i < points.size(); ++i) {
            Point p = points[i];
            glVertex3f(p.x, p.y, p.z);
        }
        } glEnd();

        glPopMatrix();                              // Restore Matrixes
    }
    void addDestination(float x, float y, float z) {
        Point p = Point(x, y, z);
        destinations.push_back(p);
    }
    void moveTowardsDestination() {
        float speed = .04;
        if(doneMoving()) {
            return;
        }
        Point dest = destinations[0];
        Point diff = dest - loc;
        if(diff.size() < .09) {
            destinations.erase(destinations.begin());
            return;
        }
        Point dir = diff.unitVector();
        loc = loc + (speed * dir);
    }
    bool doneMoving() {
        return destinations.size() == 0;
    }
};
#endif
