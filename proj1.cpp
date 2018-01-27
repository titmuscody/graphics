#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#include "colors.h"
#include "circle.h"

// Global Vars
static int rotation = 0;
Circle circle = Circle();

static int AniOn = 0;          // Animation Flag
                               //    0 - Animation Off
                               //    1 - Animation On




// Generate the scene to Display
void display() {
  glClear(GL_COLOR_BUFFER_BIT);               // Clear the Background

  circle.render();

  glPushMatrix();                             // Save Matrixes
  glRotatef(rotation, 1.0, 0.0, 0.0);
  glTranslatef(-0.5, 0.5, 0.0);
  glScalef(0.5, 0.5, 0);

  glPolygonMode(GL_FRONT, GL_LINE);
  glPolygonMode(GL_BACK, GL_FILL);

  glBegin(GL_QUAD_STRIP); {
  // draw hourglassish polygon
    vertexColor(red);
    glVertex3f(+1.0, +1.00, 0.0);
    glVertex3f(-1.0, +1.00, 0.0);
    vertexColor(green);
    glVertex3f(+0.11, +0.1, 0.0);
    glVertex3f(-0.11, +0.1, 0.0);
    vertexColor(blue);
    glVertex3f(+0.11, -0.1, 0.0);
    glVertex3f(-0.11, -0.1, 0.0);
    vertexColor(black);
    glVertex3f(+1.00, -1.00, 0.0);
    glVertex3f(-1.00, -1.00, 0.0);
  } glEnd();

  glPopMatrix();                              // Restore Matrixes

  glPushMatrix();                             // Save Matrixes
  // move triangle
  glRotatef(rotation+180, 0, 1, 0);
  glTranslatef(0.5, -0.5, 0.0);
  glScalef(0.5, 0.5, 0);
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);
  //draw triangle
  glBegin(GL_TRIANGLES); {
    glColor3f(red.r, red.g, red.b);
    glVertex3f(0, 1, 0);
    glColor3f(green.r, green.g, green.b);
    glVertex3f(-1, -1, 0);
    glColor3f(blue.r, blue.g, blue.b);
    glVertex3f(1, -1, 0);
  } glEnd();

  glPopMatrix();                              // Restore Matrixes

  glutSwapBuffers();                          // Swap Buffers
  glFlush();                                  // Force GL Command to complete
}

// A rather standard init taken for exising code
void init() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);        // Orthographic Perspective
                                                   //    left   -1.0  -x
                                                   //    right   1.0  +x
                                                   //    bottom -1.0  -y
                                                   //    top     1.0  +y
                                                   //    near   -2.0  -z
                                                   //    far     2.0  +z

  glClearColor(white.r, white.g, white.b, 0.0); // Background Color
  glShadeModel(GL_SMOOTH);                         // Smooth Shading Model
}

// Callback used when resizing window
void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);  // Orthographic Perspective
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
 
void rotateObjects(int _) {
    rotation += 2;
    if(rotation > 360)
        rotation -= 360;
  glutTimerFunc(100, rotateObjects, 0);
}

void moveCircle(int _) {
    if(circle.doneMoving()) {
        AniOn = 0;
        return;
    } else {
        circle.moveTowardsDestination();
    }
    glutTimerFunc(65, moveCircle, 0);
}

void redisplay(int _) {
  glutPostRedisplay();
  glutTimerFunc(33, redisplay, 0);
}


// Callback used when pressing or releasing a mouse button
// button is one of
//        GLUT_LEFT_BUTTON
//        GLUT_MIDDLE_BUTTON
//        GLUT_RIGHT_BUTTON
// state is one of
//        GLUT_UP
//        GLUT_DOWN
// x,y give the position on the screen
void mouse(int button, int state, int x, int y) {
  printf("Mouse %d", AniOn);

  switch(button) {
  case GLUT_LEFT_BUTTON:
    printf(" LEFT \n");
    if (state == GLUT_DOWN) {
        GLint viewport[4];
        GLdouble mvmatrix[16], projmatrix[16];
        GLint realy; /* OpenGL y coordinate position */
        GLdouble wx, wy, wz; /* returned world x, y, z coords */

        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
        glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);/* note viewport[3] is height of window in pixels */
        realy = viewport[3] -(GLint) y -1;
//        printf("Coordinates at cursor are (%4d, %4d)\n",x, realy);
//        gluUnProject((GLdouble) x, (GLdouble) realy, 0.0,mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
//        printf("World coords at z=0.0 are (%f, %f, %f)\n",wx, wy, wz);
        gluUnProject((GLdouble) x, (GLdouble) realy, 1.0,mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
//        printf("World coords at z=1.0 are (%f, %f, %f)\n",wx, wy, wz);

        circle.addDestination(wx, wy, 0);
        if(AniOn == 0) {
            AniOn = 1;
            glutTimerFunc(100, moveCircle, 0); // call spinTXDisply
        }
        break;
    }
                                                   // if Animation Off
                                                   // Then
//    if ((AniOn==0) && (state == GLUT_DOWN)) {
//      AniOn = 1;                                   // Animation On
//      circle.loc.x = 0.25;
//    }
//    else                                           // Else
                                                   // if Left Button Up

//      if (state == GLUT_UP) {
//	AniOn = 0;                                 // Animation Off
//      circle.loc.x = -0.25;

	// glutIdleFunc(NULL);                     // No idle function

//	glutTimerFunc(100, spinTXDisplay, AniOn); // call spinTXDisply
	                                          //  in 100 msec
                                                  //  with Animation Off
//      }
//    break;
//  case GLUT_RIGHT_BUTTON:
//    printf(" RIGHT \n");
//    if ((AniOn==0) && (state == GLUT_DOWN)) {
//      AniOn = 1;
//      // glutIdleFunc(spinZDisplay);
////       glutTimerFunc(100, spinTZDisplay, AniOn);
//    }
//    else
//      if (state == GLUT_UP) {
//	AniOn = 0;
//	// glutIdleFunc(NULL);
////	 glutTimerFunc(100, spinTZDisplay, AniOn);
//      }
//    break;
//  case GLUT_MIDDLE_BUTTON:                    // Reset the scene
//    if (state == GLUT_DOWN) {
//      glutPostRedisplay();
//    }
//
//    break;
//  default:
//    break;
  }
//  fflush(stdout);                             // Force output to stdout

}

int main(int argc, char** argv) {
  glutInit(&argc, argv);                  // Init the GLUT Library
  // Set the mode for the window to be opened
  // Modes
  //   GLUT_RGB same as GLUT_RGBA
  //   GLUT_RGBA use RGBA mode for color vs using index color mode
  //   GLUT_SINGLE use a single color buffer
  //   GLUT_DOUBLE use two color buffers for double buffering
  //   GLUT_DEPTH  setup a depth buffer for hidden line removal
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  

  // Set the size of the window in pixels; width then height
  glutInitWindowSize(800, 800);

  // Set the position in pixels; x the y
  // The origin of the window is at the upper left corner.
  // Use glutFullScreen() to make the window full screen
  glutInitWindowPosition(100, 100);

  // Create a top-level window, the name should be placed on the
  // title bar of the window
  glutCreateWindow("Project 1 Shapes");

  // Init function written by developer
  init();

  // Set a callback function to draw what will be displayed on the screen
  // The display function must redraw the scene from scratch each time it
  // is envoked.
  glutDisplayFunc(display);

  // Set a callback function for when the window is resized.
  glutReshapeFunc(reshape);

  // Set a callback fucntion for when a mouse button is 
  // pressed or released.
  // See the callback function mouse
  glutMouseFunc(mouse);

  // Invoke an event loop
  // The event loop will run until the program is terminated.
  // The event loop handle envoking callback function as necessary
  // based upon events it receives.
  glutTimerFunc(100, rotateObjects, 0);
  glutTimerFunc(100, redisplay, 0);
  glutMainLoop();
  return 0;
}
