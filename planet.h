#ifndef PLANET_H
#define PLANET_H
#include <GL/gl.h>

#include <math.h>
#include <vector>




#include "colors.h"
#include "point.h"
#include "graphic.h"

using std::vector;

class Planet {

    float passed_time;
    public:
    Point radius;
    float anim_time;
    Drawable *draw;
    Point offset;
    float time_offset;

    vector<Planet> moons;
    Planet(Point rad, float orbit_time, Point offset, Drawable *d) {
        passed_time = 0;
        time_offset = 0;
        this->radius = rad;
        this->offset = offset;
        anim_time = orbit_time;
        draw = d;
    }
    float getx() {
        float fin_ratio = get_done_ratio();
        float rad = fin_ratio * 2 * M_PI;
        float pos = radius.x * cos(rad);
        return pos + offset.x;
    }
    float gety() {
        float fin_ratio = get_done_ratio();
        float rad = fin_ratio * 2 * M_PI;
        float pos = radius.y*sin(rad);
        return pos + offset.y;
    }
    float getz() {
        float fin_ratio = get_done_ratio();
        float rad = fin_ratio * 2 * M_PI;
        float pos = radius.z*sin(rad);
        return pos + offset.z;
    }
    float get_rotation() {
        float fin_ratio = get_done_ratio();
        float rad = fin_ratio * 360;
        return rad;
    }
    // rotates every ten seconds
    // return number between 0 and 1
    float get_done_ratio() {
        float percent = (anim_time - passed_time) / anim_time;
        percent += time_offset;
        if(percent > 1) {
            percent -= 1;
        }
        return percent;
    }
    Point get_position() {
        return Point(getx(), gety(), getz());
    }
    void update_position(float time) {
        if(passed_time > anim_time)
            passed_time = 0;
        passed_time += time;
    }
     void render(float time) {
        update_position(time);

        float cx = getx();
        float cy = gety();
        float cz = getz();

        glPushMatrix();                             // Save Matrixes

        glTranslatef(cx, cy, cz);
        glPushMatrix();
            if(anim_time > 0) {
                glRotatef(get_rotation(), 0, 1, 0);
            }
            draw->render(time);
        glPopMatrix();

        for(int i = 0; i < moons.size(); ++i) {
            moons[i].render(time);
        }

        glPopMatrix();                              // Restore Matrixes
    }
};
#endif
