#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

// Color Structure
typedef struct {
  GLfloat r;     // Red
  GLfloat g;     // Green
  GLfloat b;     // Blue
} rgb;


// Colors
static rgb skyBlue = {0.529, .807, 1.0};
static rgb red = {1.0, 0.0, 0.0};
static rgb offWhite = {0.87, 0.87, 0.87};
static rgb white = {1.0, 1.0, 1.0};
static rgb yellow = {1.0, 1.0, 0.};
static rgb aqua = {127.0/255.0, 1.0, 212.0/255.0};
static rgb seaGreen = {0.329, 1.0, 0.6};
static rgb lavenderBlush = {1.0, 240.0/255.0, 245.0/255.0};
static rgb honeydew = {0.941, 1.0, 0.941};
static rgb coral = {1.0, 114.0/255.0, 86.0/255.0};
static rgb magenta = {1.0, 0.0, 1.0};
static rgb navajoWhite = {1.0, 222.0/255.0, 173.0/255.0};
static rgb blue = {0.0, 0.0, 1.0};
static rgb cadetBlue = {152.0/255.0, 245.0/255.0, 1.0};
static rgb green = {0.0, 1.0, 0.0};
static rgb olive = {192.0/255.0, 1.0, 62.0/255.0};
static rgb gold = {1.0, 215.0/255.0, 0.0};

static GLfloat eyeX = 0.0;
static GLfloat eyeY = 0.0;
static GLfloat eyeZ = 2.0;

// Generate the scene to Display
void display() {
  glClear(GL_COLOR_BUFFER_BIT);               // Clear the Background
  glPushMatrix();                             // Save Matrixes

  glBegin(GL_POLYGON); {                      // Create a Trangle
    glColor3f(yellow.r, yellow.g, yellow.b);  // inside a Cube
    glVertex3f(0.0, 0.5, 0.0);
    glColor3f(red.r, red.g, red.b);
    glVertex3f(-0.5, -0.5, 0.0);
    glColor3f(white.r, white.g, white.b);
    glVertex3f(0.5, -0.5, 0.0);
  } glEnd();

  glutWireCube(1.0);
  glPopMatrix();                              // Restore Matrixes

  glPushMatrix();                             // Move to a new position
  glColor3f(blue.r, blue.g, blue.b);          // Create a BLUE
  glTranslatef(1.25, 0.0, -0.750);            // Wire Frame Sphere
  glutWireSphere(0.35, 15, 5);
  glPopMatrix();

  glPushMatrix();                             // Move to a new position
  glColor3f(gold.r, gold.g, gold.b);          // Create a GOLD
  glTranslatef(-1.25, 0.0, -0.55);            // Wire Frame Cube
  glutWireCube(0.35);
  glPopMatrix();

  glutSwapBuffers();                          // Swap Buffers
  glFlush();                                  // Force GL Command to complete
}

// A rather standard init taken for exising code
void init() {
  glClearColor(skyBlue.r, skyBlue.g, skyBlue.b, 0.0); // Background Color
  glShadeModel(GL_SMOOTH);                            // Smooth Shading Model
}

// Callback used when resizing window
void reshape(int w, int h) {
  printf("reshape w %d, h %d\n", w, h);
  fflush(stdout);
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);   // Set the viewport
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
                                           // Perspective Projection
  gluPerspective(100.0,                    // field of view is 100 degrees
		 (GLfloat)w/(GLfloat)h,    // aspect ratio is w/h
		 1.0,                      // near clipping point (positive)
                 20.0);                    // far clipping point (positive)

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
                                          // Set where the camera is
  gluLookAt(0.0, 0.0, 2.0,                // Eye - x, y, z
	    0.0, 0.0, 0.0,                // Center - x, y, z
	    0.0, 1.0, 0.0);               // Up - x, y, z
}

void keyboard(unsigned char key, int x, int y) {

  glLoadIdentity();
  switch(key) {
  case '0':
    eyeX = 0.0;
    eyeY = 0.0;
    eyeZ = 2.0;
    break;
  case '1':
    eyeX += 0.125;
    eyeY += 0.125;
    break;
  case '2':
    eyeX += 0.125;
    eyeY += -0.125;
    break;
  case '3':
    eyeX += -0.125;
    eyeY += -0.125;
    break;
  case '4':
    eyeX += -0.125;
    eyeY += 0.125;
    break;
  case 'z':
    eyeZ += -0.125;
    break;
  case 'Z':
    eyeZ += 0.125;
    break;
  case 'y':
    eyeY += -0.125;
    break;
  case 'Y':
    eyeY += 0.125;
    break;
  case 'x':
    eyeX += -0.125;
    break;
  case 'X':
    eyeX += 0.125;
    break;

  }
  
  gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glutPostRedisplay();
} 


int main(int argc, char** argv) {

  glutInit(&argc, argv);                  
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Double Buffer On
                                                             // RGB Color Model
                                                             // Hidden Surface Removal
  glutInitWindowSize(650, 650);
  glutInitWindowPosition(200, 0);
  glutCreateWindow("Camera");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);                               // Keyboard Callback
  glutMainLoop();
  return 0;
}
