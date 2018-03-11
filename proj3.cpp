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
#include "fish.h"

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

Camera cam = Camera(Point(0, 0, 15));
std::vector<Planet> planets;

void add_camera_movements() {
    cam.move_to(Point(15, 0, 0), 5);
    cam.move_to(Point(0, 0, 15), 5);
    cam.move_to(Point(0, 0, 5), 5);
    cam.move_to(Point(0, 0, -15), 5);
}

void init() {

	GLuint scaleTex;
  char const* tfile = "Colorful-Fish-scale.raw";
  int width = 512;
  int height = width;
  unsigned char* bits;
  if (tfile != NULL) {                 // Read the .raw texture
                                       // into memory at bits
    FILE *rawFile;
    rawFile = fopen(tfile, "rb");            // Open the .raw file r=read b=binary
    if (rawFile == NULL) {
      printf("Error problem reading %s\n", tfile);
      return;
    }
    long size = width*height*4;              // 4 bytes per bit RGBA
    bits = (unsigned char*) malloc(size+10); // allocate space for the file in
                                             // memory, not sure why +10
                                             // found as an example 
    long cnt = fread(bits, 1, size, rawFile); // Read into bits
                                              // size number of bytes (1=bytes)
                                              // from rawFile 
    fclose(rawFile);                          // Close the File when done

    if (cnt != size)                          // Check that we got the bytes
      printf("Not enough bits %d\n", cnt);    // asked for
  
    printf("File %d X %d (%d)\n", width, height, size);
    fflush(stdout);
  }


  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Set pixel storage mode
                                          // To fully understand this
                                          // command is beyond where I want
                                          // where I want to go in this class
                                          // see pg 325 for details

  glGenTextures(1, &scaleTex);             // Will return 1 unused texture
                                          // object name in texName

  glBindTexture(GL_TEXTURE_2D, scaleTex);  // Initial bind,
                                          // code will work without this
                                          // but documentation indicates
                                          // it should be done?

  glTexParameteri(GL_TEXTURE_2D, 
		  GL_TEXTURE_WRAP_S, GL_REPEAT);   // Tile image if texture coor > 1.0
  glTexParameteri(GL_TEXTURE_2D, 
		  GL_TEXTURE_WRAP_T, GL_REPEAT);   // Tile image if texture corr > 1.0
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
		  GL_NEAREST);                                    // Use nearest texel when mag
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
		  GL_NEAREST);                                    // Use nearest texel when min

  glTexImage2D(GL_TEXTURE_2D,             // Load a 2D image
	       0, 
	       GL_RGBA, 
	       width,        height,       
	       0,
	       GL_RGBA, 
	       GL_UNSIGNED_BYTE, 
	       bits); 





  planets.push_back(Planet(Point(), -1, Point(), new Fish(scaleTex)));

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
	Point l = cam.get_orientation();
  gluLookAt(c.x, c.y, c.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


//  float time_diff = get_time_passed();
  for(int i = 0; i < planets.size(); ++i) {
    planets[i].render(.06);
  }


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
}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
		case 27:
			exit(0);
			break;
		case 'a':
			//cam.x -= 1;
			//camx -= 1;
			break;
		case 'w':
			//camy += 1;
			break;
		case 's':
			//camy -= 1;
			break;
		case 'd':
			//camx += 1;
			break;
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
  glutMainLoop();
  return 0;
}
