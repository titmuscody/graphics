#include <GL/gl.h>

#include <math.h>
#include <vector>


#ifndef PLANET_H
#define PLANET_H


#include "colors.h"
#include "point.h"

using std::vector;

class Planet {

    public:
    float passed_time;
    float sphere_radius;
    float x_radius;
    float y_radius;
    float z_radius;
    float anim_time;
    Color planet_color;
    Planet(float radius, float xrad, float yrad, float zrad, float orbit_time, Color c) {
        passed_time = 0;
        sphere_radius = radius;
        x_radius = xrad;
        y_radius = yrad;
        z_radius = zrad;
        anim_time = orbit_time;
        planet_color = c;
    }
    float getx() {
        float fin_ratio = get_done_ratio();
        float rad = fin_ratio * 2 * M_PI;
        return x_radius * cos(rad);
    }
    float gety() {
        float fin_ratio = get_done_ratio();
        float rad = fin_ratio * 2 * M_PI;
        return y_radius*sin(rad);
    }
    float getz() {
        return 0;
    }
    // rotates every ten seconds
    // return number between 0 and 1
    float get_done_ratio() {
        return (anim_time - passed_time) / anim_time;
    }
    Point get_position() {
        return Point(getx(), gety(), getz());
    }
     void render(float time) {
        if(passed_time > anim_time)
            passed_time = 0;
        passed_time += time;

        float cx = getx();
        float cy = gety();
        float cz = getz();

        glPushMatrix();                             // Save Matrixes

        glTranslatef(cx, cy, cz);
        vertexColor(planet_color);
        glutSolidSphere(sphere_radius, 20, 16);

        glPopMatrix();                              // Restore Matrixes
    }
};
#endif
