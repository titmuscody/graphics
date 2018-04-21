//#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <sys/time.h>
#include <vector>

#include "colors.h"
#include "camera.h"
#include "level.h"
#include "ball.h"

using std::vector;

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

GLfloat globalAmbientLight[] = {0.15, 0.15, 0.15, 1.0};

Camera cam = Camera(Point(0, 40, 60));
Level* lvl;
Ball* ball;
bool falling = false;
float xrot = 0;
float yrot = 0;
float xclick;
float yclick;
float xtemprot = 0;
float ytemprot = 0;

void init_objects() {
	cam.set_orientation(Point(0, 50, 0));
	lvl = new Level();
	ball = new Ball();
}

void init() {
	srand(time(NULL));
	printf("Camera Controls\n");
	printf("w - up\ns - down\na - left\nd - right\n");
	printf("q - zoom out\ne - zoom in\n");
	
	printf("level changes\n g - add gaussian filter to terrain\n");
	printf("m - add mean filter to terrain\n");
	printf("r - reset level and regenerate terrain\n");

	printf("ball movement\n");
	printf("i - up\nk - down\nj - left\nl - right\n");
	printf("space bar - reset ball / start ball movement\n");

	init_objects();

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
}

void move(int i) {
	if(falling) {
		ball->add_vel(Point(0, -0.07, 0));
		ball->update_position(.06);
		lvl->touching(ball);
	}
	cam.update_position(.06);
  glutPostRedisplay();
}


void display() {

  glClear(GL_COLOR_BUFFER_BIT | 
      GL_DEPTH_BUFFER_BIT);  // clear color and depth buffer

  glPushMatrix();
  Point c = cam.get_position();
	Point l = cam.get_orientation();
  gluLookAt(c.x, c.y, c.z, l.x + xtemprot, l.y + ytemprot, l.z, 0.0, 1.0, 0.0);

	lvl->render(.06);
	ball->render(.06);

  glPopMatrix(); // Pop off the look matrix

  glutSwapBuffers();
  glutTimerFunc(60, move, 0);
}



void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0, (GLfloat)w/(GLfloat)h, 0.5, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void special(int key, int x, int y) {
}

void keyboard(unsigned char key, int x, int y) {
	float radius = 7;
  switch(key) {
		case 27:
			exit(0);
			break;
		case 'e':
			cam.add_vel((cam.lookat - cam.pos).unitVector());
			break;
		case 'q':
			cam.add_vel((cam.pos - cam.lookat).unitVector());
			break;
		case 'w':
			cam.add_vel((cam.pos - cam.lookat).cross(Point(1, 0, 0)).unitVector());
			break;
		case 's':
			cam.add_vel(Point(1, 0, 0).cross(cam.pos - cam.lookat).unitVector());
			break;
		case 'd':
			cam.add_vel(Point(0, 1, 0).cross(cam.pos - cam.lookat).unitVector());
			break;
		case 'a':
			cam.add_vel((cam.pos - cam.lookat).cross(Point(0, 1, 0)).unitVector());
			break;
		case 'r':
			delete lvl;
			lvl = new Level();
			break;
		case 'i':
			if(!falling) {
				ball->pos = ball->pos + Point(0, 0, -1);
			}
			break;
		case 'j':
			if(!falling) {
				ball->pos = ball->pos + Point(-1, 0, 0);
			}
			break;
		case 'k':
			if(!falling) {
				ball->pos = ball->pos + Point(0, 0, 1);
			}
			break;
		case 'l':
			if(!falling) {
				ball->pos = ball->pos + Point(1, 0, 0);
			}
			break;
		case 'g':
			lvl->add_gauss_filter();
			break;
		case 'm':
			lvl->add_mean_filter();
			break;
		case ' ':
			if(falling) {
				delete ball;
				ball = new Ball();
			}
			falling = !falling;
			break;
		default:
			break;
  }
}


void mouseEvent(int button, int state, int x, int y) {
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		xclick = x;
		yclick = y;
	}

	if(state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
		Point loc = cam.get_orientation();
		loc = loc + Point(xtemprot, ytemprot, 0);
		cam.set_orientation(loc);

		//xrot += xtemprot;
		//yrot += ytemprot;
		xtemprot = 0;
		ytemprot = 0;
	}
}
void mouseMove(int x, int y) {
	xtemprot = (xclick - x) / 5;
	ytemprot = (yclick - y) / 5;
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 850);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Fish Tank");

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
	glutMouseFunc(mouseEvent);
	glutMotionFunc(mouseMove);
  glutTimerFunc(70, move, 0);
  glutMainLoop();
  return 0;
}
