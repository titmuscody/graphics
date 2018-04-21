#include <GL/gl.h>

#ifndef COLORS_H
#define COLORS_H

// Color Structure
typedef struct {
  GLfloat r;     // Red
  GLfloat g;     // Green
  GLfloat b;     // Blue
} rgb;
class Color {
    public:
    float r;
    float g;
    float b;
    float specr;
    float specb;
    float specg;
    float shinr;
    float shing;
    float shinb;
    Color() {
        r = 1;
        g = 1;
        b = 1;
    }
    Color(float red, float gr, float bl) {
        r = red;
        g = gr;
        b = bl;
    }
    Color(float red, float green, float blue, float spr, float spg, float spb, float shr, float shg, float shb) {
        r = red;
        g = green;
        b = blue;
        specr = spr;
        specg = spg;
        specb = spb;
        shinr = shr;
        shing = shg;
        shinb = shb;
    }
};


// Colors
static Color blue = Color(0, 0, 1);
static Color red = Color(1, 0, 0);
static Color green = Color(0, 1, 0);
static Color white = Color(1, 1, 1);
static Color black = Color(0, 0, 0);
static Color orange = Color(1, 140.0/255.0, 0);
static Color grey = Color(140.0/255.0, 140.0/255.0, 140.0/255.0);
static Color yellow = Color(1.0, 1.0, 0);
static Color purple = Color(210.0/255.0, 157.0/255.0, 239.0/255.0);
static Color brown = Color(156.0/255.0, 49.0/255.0, 24.0/255.0);

static Color yellowFace = Color(1, 1, 0, .2, .2, .2, .9, .9, .9);
static Color madFace = Color(1, 0, 0, .2, .2, .2, .4, .4, .4);
static Color devilFace = Color(purple.r, purple.g, purple.b, 1, 1, 1, .8, .8, .8);
static Color eye = Color(1, 1, 1, .8, .8, .8, .4, .4, .4);
static Color pupil = Color(0, 0, 0, .2, .2, .2, .4, .4, .4);
static Color sun = Color(green.r, green.g, green.b, 1, 1, 1, 2, 2, 2);
static Color sunRay = Color(orange.r, orange.g, orange.b, 1, 1, 1, .8, .8, .8);

void vertexColor(Color val) {
    glColor3f(val.r, val.g, val.b);
}

void materialColor(Color val) {
    GLfloat prop[] = {0, 0, 0, 1.0};
    prop[0] = val.r;
    prop[1] = val.g;
    prop[2] = val.b;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, prop);
    prop[0] = val.specr;
    prop[1] = val.specg;
    prop[2] = val.specb;
    glMaterialfv(GL_FRONT, GL_SPECULAR, prop);
    prop[0] = val.shinr;
    prop[1] = val.shing;
    prop[2] = val.shinb;
    glMaterialfv(GL_FRONT, GL_SHININESS, prop);
}


#endif
