#include <GL/gl.h>

#include <math.h>
#include <vector>


#ifndef CAMERA_H
#define CAMERA_H


#include "colors.h"
#include "point.h"
#include "graphic.h"

using std::vector;

class Camera {

    Point cur_dest;
    Point start;
    float anim_time;
    float passed_time;
    vector<Point> destinations;
    vector<float> times;
    float get_done_percent() {
        if(anim_time < passed_time) {
            return 1;
        }
        float percent = 1 - (anim_time - passed_time) / anim_time;
        return percent;
    }
    float getx() {
        float per = get_done_percent();
        float movement = (cur_dest.x - start.x) * per;
        return start.x + movement;
    }
    float gety() {
        float per = get_done_percent();
        float movement = (cur_dest.y - start.y) * per;
        return start.y + movement;
    }
    float getz() {
        float per = get_done_percent();
        float movement = (cur_dest.z - start.z) * per;
        return start.z + movement;
    }
    public:
    Camera(Point orig) {
        cur_dest = orig;
        anim_time = .00001;
        start = orig;
    }
    void move_to(Point p, float duration) {
        destinations.push_back(p);
        times.push_back(duration);
    }
    void update_position(float time) {
        passed_time += time;
        if(passed_time > anim_time) {
            if(destinations.size() > 0) {
                start = cur_dest;
                cur_dest = destinations[0];
                destinations.erase(destinations.begin());
                anim_time = times[0];
                times.erase(times.begin());
                passed_time = 0;
            }
        }
    }
    Point get_position() {
        return Point(getx(), gety(), getz());
    }
    Point get_orientation() {
        return Point(0, 0, 0);
    }
    bool done_moving() {
        return destinations.size() == 0 && passed_time > anim_time;
    }
};
#endif
