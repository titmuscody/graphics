//#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <sys/time.h>
#include <vector>

#include "planet.h"
#include "colors.h"
#include "camera.h"
#include "smile.h"

/*
  Hidden Surface Removal Steps:
  1) Add GLUT_DETH to glutInitDisplayMode
  2) Call glEnable(GL_DEPTH_TEST) after window is created
  3) Add GL_DEPTH_BUFFER_BIT to glClear

  Lighting Steps:
  1) Define normal vectors
     glutSolidSphere does this for us!
  2) Create, and position light sources
     glLight*
     glEnable
  3) Create and select lighting model
     
  4) Define material properties
*/



GLfloat lightPosition0[] = {-0.75, 1.0, 2.0, 1.0}; 
GLfloat lightAmbient0[] =  {0.5, 0.5, 0.5, 1.0}; // Default
GLfloat lightDiffuse0[] =  {0.1, 0.1, 0.1, 1.0}; // Default
GLfloat lightSpecular0[] = {0.2, 0.2, 0.2, 1.0}; // Default

GLfloat lightPosition1[] = {0.75, 1.0, -2.0, 1.0};
GLfloat lightAmbient1[] =  {0.02, 0.02, 0.02, 1.0}; // Default
GLfloat lightDiffuse1[] =  {0.1, 0.1, 0.1, 1.0}; // Default
GLfloat lightSpecular1[] = {0.4, 0.4, 0.4, 1.0}; // Default

GLfloat spot_direction[] = {0.0, 0.0, -1.0};
int SPOT_LIGHT = 0;

//GLfloat globalAmbientLight[] = {0.0, 0.0, 0.0, 1.0};
GLfloat globalAmbientLight[] = {0.15, 0.15, 0.15, 1.0};



float camlookx = 0;
float camlooky = 0;
float camlookz = 0;
Camera cam = Camera(Point(0, 0, 15));
std::vector<Planet> planets;
bool light1 = true;

static double d2r = 3.14159/180.0;  // Degree to radian conversion

void add_camera_movements() {
    cam.move_to(Point(15, 0, 0), 5);
    cam.move_to(Point(0, 0, 15), 5);
    cam.move_to(Point(0, 0, 5), 5);
    cam.move_to(Point(0, 0, 30), 5);
}

void init() {
  Planet p = Planet(Point(4, 0, 8), 8, Point(0, 0, -7), new SurpriseFace());
  p.moons.push_back(Planet(Point(2, 2, 0), 3, Point(), new AngryFace()));
  p.moons.push_back(Planet(Point(6, 6, 0), 8, Point(), new DevilFace()));
  planets.push_back(p);

  p = Planet(Point(-8, 18, 0), 24, Point(0, -10, 0), new AngryFace());
  planets.push_back(p);

  p = Planet(Point(14, 18, 0), 24, Point(0, 10, 0), new DevilFace());
  p.time_offset = .5;
  p.moons.push_back(Planet(Point(3, 3, 0), 4, Point(), new AngryFace()));
  p.moons.push_back(Planet(Point(2, 2, 0), 3, Point(), new SurpriseFace()));
  p.moons.push_back(Planet(Point(6, 6, 0), 8, Point(), new AngelFace()));
  planets.push_back(p);

  planets.push_back(Planet(Point(), -1, Point(), new Sun()));

  add_camera_movements();


  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);

    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
           globalAmbientLight);           // Ambient Light in Scene

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,
          GL_TRUE);                       // Gives more realistic result
                                                  // but is slower in computation

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,
          GL_FALSE);                       // Only light front faces
                                                   // We use all spheres so
                                                   // this is OK

    // Enable Lighting and Hidden Surface Removal
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    light1 = true;
}


void switchLights(int i) {
  if(light1) {
    light1 = false;
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
  } else {
    light1 = true;
    glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
  }
  glutTimerFunc(4000, switchLights, 0);
}

void move(int i) {
  if(cam.done_moving()) {
    add_camera_movements();
  }
  glutPostRedisplay();
}

void display() {
  GLfloat cx, cy, cz = 0.0;      // X, Y, Z position of planet

  glClear(GL_COLOR_BUFFER_BIT | 
      GL_DEPTH_BUFFER_BIT);  // clear color and depth buffer

//  glEnable(GL_COLOR_MATERIAL);   // Using glColorMaterial allows planets
                                 // to just use the color set by
                                 // glColor as a material setting

  glPushMatrix();
  cam.update_position(.06);
  Point c = cam.get_position();
//  printf("point %f %f %f\n", c.x, c.y, c.z);
//  gluLookAt(0, 0, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  gluLookAt(c.x, c.y, c.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


//  float time_diff = get_time_passed();
  for(int i = 0; i < planets.size(); ++i) {
    planets[i].render(.06);
  }


//  if (SPOT_LIGHT) {
//    glPushMatrix();                       // Spot Light Direction
//    glTranslatef(spot_direction[0], spot_direction[1], spot_direction[2]);
//    glColor3f(0.0, 1.0, 0.0);
//    glutSolidSphere(0.45, 20, 16);  // Put a Sphere to show where spot light is pointing!
//    glPopMatrix();
//  }


  glPopMatrix(); // Pop off the look matrix

//  glDisable(GL_COLOR_MATERIAL);         // Turn off glColorMaterial

  glutSwapBuffers();
  glutTimerFunc(70, move, 0);
}



void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0, (GLfloat)w/(GLfloat)h, 0.5, 80.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void special(int key, int x, int y) {

//  switch(key) {
//  case GLUT_KEY_UP:
//    spot_direction[1] += 0.1;
//    break;
//  case GLUT_KEY_DOWN:
//    spot_direction[1] -= 0.1;
//    break;
//  case GLUT_KEY_LEFT:
//    spot_direction[0] -= 0.1;
//    break;
//  case GLUT_KEY_RIGHT:
//    spot_direction[0] += 0.1;
//    break;
//  default:
//    break;
//  }
//
//  /*  glLoadIdentity();
//      gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); */
//  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//  printf("Spot Light at (%f, %f, %f)\n",
//     spot_direction[0],
//     spot_direction[1],
//     spot_direction[2]);




}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
  case 'A':
    // Change the Color of Global Ambient Light from black (0,0,0) to white (1,1,1)
    if (globalAmbientLight[0] >= 1.0) break;
    globalAmbientLight[0] += 0.2;
    globalAmbientLight[1] += 0.2;
    globalAmbientLight[2] += 0.2;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
		   globalAmbientLight);           // Ambient Light in Scene
    break;
  case 'a':
    if (globalAmbientLight[0] <= 0.0) break;
    globalAmbientLight[0] -= 0.2;
    globalAmbientLight[1] -= 0.2;
    globalAmbientLight[2] -= 0.2;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,
		   globalAmbientLight);           // Ambient Light in Scene
//    camx -= 1;
    break;
//  case 'w':
//    camy += 1;
//    break;
//  case 's':
//    camy -= 1;
//    break;
//  case 'd':
//    camx += 1;
//    break;
  case 'D':
//     Change the Color of Diffuse light
    if (lightDiffuse0[0] >= 1.0) break;
    lightDiffuse0[0] += 0.2;
    lightDiffuse0[1] += 0.2;
    lightDiffuse0[2] += 0.2;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
    //    glutPostRedisplay();
    break;
  case 'd':
    if (lightDiffuse0[0] <= 0.0) break;
    lightDiffuse0[0] -= 0.2;
    lightDiffuse0[1] -= 0.2;
    lightDiffuse0[2] -= 0.2;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
    //    glutPostRedisplay();
    break;
  case 'S':
    // Change the Color of Specular Light
    if (lightSpecular0[0] >= 1.0) break;
    lightSpecular0[0] += 0.2;
    lightSpecular0[1] += 0.2;
    lightSpecular0[2] += 0.2;
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);
    //    glutPostRedisplay();
    break;
  case 's':
    if (lightSpecular0[0] <= 0.0) break;
    lightSpecular0[0] -= 0.2;
    lightSpecular0[1] -= 0.2;
    lightSpecular0[2] -= 0.2;
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);
    //    glutPostRedisplay();
    break;
//  case 'b':
//  SPOT_LIGHT = 0;
//    lightPosition0[0] = 0.0; //x
//    lightPosition0[1] = 0.0; //y
//    lightPosition0[2] = 1.0; //z
//    lightPosition0[3] = 0.0; // make it NOT a spot light
//	 glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient0);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);
//	break;
// case 'B':
//    SPOT_LIGHT = 1;
//    /*    glLoadIdentity();
//	  gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); */
//    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);
//    lightPosition0[0] = 0.0; //x
//    lightPosition0[1] = 0.0; //y
//    lightPosition0[2] = 1.0; //z
//    lightPosition0[3] = 1.0; // make it a spot light
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//
//    break;
  default:
    break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1150, 850);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Sun");

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
//  glutTimerFunc(70, move, 0);
  glutTimerFunc(3000, switchLights, 0);
  glutMainLoop();
  return 0;
}
