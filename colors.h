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
};


// Colors
static Color blue = Color(0, 0, 1);
static Color red = Color(1, 0, 0);
static Color green = Color(0, 1, 0);
static Color white = Color(1, 1, 1);
static Color black = Color(0, 0, 0);
static Color orange = Color(1, 140.0/255.0, 0);

void vertexColor(Color val) {
    glColor3f(val.r, val.g, val.b);
}


#endif
