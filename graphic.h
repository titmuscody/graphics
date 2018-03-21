#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "point.h"
#include "vector"

using std::vector;

class Drawable {
	public:
		virtual void render(float) = 0;
};

class Mover {
	public:
		virtual Point get_position(float) = 0;
};

class CompMover : public Mover {
	vector<Mover*> anims;
	vector<float> times;
	int i = 0;
	float time;
	
	public:
	void add(Mover* m, float t) {
		anims.push_back(m);
		times.push_back(t);
	}
	Point get_position(float t) {
		time += t;
		if(time > times[i]) {
			time = 0;
			i = (i + 1) % times.size();
		}
		return anims[i]->get_position(t);
	}
};

class OffsetMover : public Mover {
	Point offset;
	public:
	OffsetMover(Point p) {
		offset = p;
	}
	Point get_position(float time) {
		return offset;
	}
};

class PathMover : public Mover {
	float passed_time = 0;
	float anim_time;
	Point start;
	Point end;
	public:
	PathMover(Point s, Point e, float anim) {
		anim_time = anim;
		start = s;
		end = e;
	}
	Point get_position(float time) {
		passed_time += time;
		if(passed_time > anim_time) {
			passed_time -= anim_time;
		}
		float finished = passed_time / anim_time;
		return start + (finished * (end - start));
	}
};

class SpinDrawable : public Drawable {
	Drawable* draw;
	float passed_time;
	float anim_time;
	bool disable = false;
	bool deactivate = false;
	public:
		SpinDrawable(Drawable* d, float rot_time, bool stop) {
			draw = d;
			anim_time = rot_time;
			deactivate = stop;
		}
		void render(float time) {
			passed_time += time;
			if(passed_time > anim_time) {
				if(deactivate) {
					disable = true;
				}
				passed_time -= anim_time;
			}
			GLfloat rotation = (passed_time / anim_time) * 360;
			if(disable) {
				draw->render(time);
			} else {
				glPushMatrix();
					glRotatef(rotation, 1, 1, 1);
					draw->render(time);
				glPopMatrix();
			}
		}
};

class MovingDrawable : public Drawable {
	Drawable* draw;
	Mover* mover;
	public:
		MovingDrawable(Drawable* d, Mover* m) {
			draw = d;
			mover = m;
		}
		void render(float time) {
			glPushMatrix();
				Point p = mover->get_position(time);
				glTranslatef(p.x, p.y, p.z);
				draw->render(time);
			glPopMatrix();
		}
};

class NullDrawable : public Drawable {
    public:
    void render(float time) {
    }
};

#endif
