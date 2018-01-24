#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.807, 1.0);              // Deep Sky Blue

  glBegin(GL_POLYGON); {                 // Generate a 4 point (square) polygon
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, 0.75, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
  }  glEnd();

  glFlush();                              // Force GL Command to execute
}

void init() {                             // Simple yet standard for Ortho projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); // Left, Right, Bottom, Top, Near, Far
  
  glClearColor(1.0, 0.87,0.678, 0.0);              // Navajo White
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);             // Single Buffer
  glutInitWindowSize(350, 350);                            
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Polygon - The Adventure Begins");
  init();
  glutDisplayFunc(display);           
  glutMainLoop();
  return 0;
}
