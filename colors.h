#include <GL/gl.h>

#ifndef COLORS_H
#define COLORS_H

// Color Structure
typedef struct {
  GLfloat r;     // Red
  GLfloat g;     // Green
  GLfloat b;     // Blue
} rgb;


// Colors
static rgb blue = {0, 0, 1};
static rgb red = {1, 0, 0};
static rgb green = {0, 1, 0};
static rgb white = {1, 1, 1};
static rgb black = {0, 0, 0};

void vertexColor(rgb val) {
    glColor3f(val.r, val.g, val.b);
}


#endif
