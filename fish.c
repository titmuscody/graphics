//#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>


int WINX = 800.0; //window size
int WINY = 600.0;

GLuint scaleTex;

static GLdouble zFAR = 20;
static GLfloat R = 0.0;

GLfloat zoom = 8.0; //to control camera movements
GLfloat xMovement = 0.0;
GLfloat yMovement = 0.0;

typedef struct {
  GLfloat r;
  GLfloat g;
  GLfloat b;
} rgb;

static rgb red = {255.0/255.0, 0.0, 0.0};
static rgb green = {0.0, 1.0, 0.0};
static rgb blue  = { 0.0, 0.0, 1.0};
static rgb yellow = {1.0, 1.0, 0.0};
static rgb coral = {1.0, 0.5, 0.3};
static rgb black = {0.0, 0.0, 0.0};

GLfloat lightPosition0[] = {0.0, 1.0, 6.0, 1.0}; 
GLfloat lightAmbient0[] =  {0.0, 0.0, 0.0, 1.0}; // Default
GLfloat lightDiffuse0[] =  {1.0, 1.0, 1.0, 1.0}; // Default
GLfloat lightSpecular0[] = {1.0, 1.0, 1.0, 1.0}; // Default

GLfloat globalAmbientLight[] = {0.6, 0.6, 0.6, 1.0}; 

void normalise(GLfloat x,GLfloat y,GLfloat z,GLfloat normal[3]) //to normalize a vector
{
  GLfloat mag;
  int thing;

  mag = sqrtf((x*x)+(y*y)+(z*z));

  thing = (int)ceil(mag);

  if(thing != 0)
    {
      normal[0] = x / mag;
      normal[1] = y / mag;
      normal[2] = z / mag;
    }
  else
    {
      normal[0] = 0.0;
      normal[1] = 0.0;
      normal[2] = 1.0;
    }

}

void findNormal3Points(GLfloat vector1[3],GLfloat vector2[3], 
		       GLfloat vector3[3], GLfloat normal[3])
{
  GLfloat tvector1[3],tvector2[3];
	
  //finding normal for polygon with 3 points
  //[v1-v2]X[v2-v3] -- X is the Cross Product

  //[v1-v2]
  tvector1[0] = vector1[0]-vector2[0];
  tvector1[1] = vector1[1]-vector2[1];
  tvector1[2] = vector1[2]-vector2[2];

  //[v2-v3]
  tvector2[0] = vector2[0]-vector3[0];
  tvector2[1] = vector2[1]-vector3[1];
  tvector2[2] = vector2[2]-vector3[2];

  normal[0] = (tvector1[1]*tvector2[2])-(tvector2[1]*tvector1[2]);
  normal[1] = (tvector2[0]*tvector1[2])-(tvector1[0]*tvector2[2]);
  normal[2] = (tvector1[0]*tvector2[1])-(tvector2[0]*tvector1[1]);

  normalise(normal[0],normal[1],normal[2],normal);

}


GLfloat image_height(GLfloat vector[]) {
	return vector[1] / 2.0;
}
GLfloat image_width(GLfloat vector[]) {
	return -vector[2] / 2.0;
}

// r1 < r2
// r3 < r1
// r4 < r3
void drawBody(GLfloat r1, GLfloat r2, int cuts, int stacks)
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glEnable(GL_TEXTURE_2D);                                   // Enable 2D texture mapping

 glTexEnvf(GL_TEXTURE_ENV,                                  // Define how the texture is
	   GL_TEXTURE_ENV_MODE,                             // to be used.
	   GL_ADD);                                     // As a simple texture map
                                                            // or something more complex
                                                            // (combine texture and color)

 glBindTexture(GL_TEXTURE_2D, scaleTex);                     // Indicate which 2D image to use

  GLfloat radius;
  //Equ. for a Sphere
  // But this is not a Sphere???
  //x = x_0 + r*cos(phi)*sin(theta) 
  //y = y_0 + r*sin(phi)*sin(theta) 0 <= phi <= 2*pi , 0 <= theta <= pi )
  //z = z_0 + r*cos(theta) 

  int i,j;
  float DEG2RAD = 3.141592653589793/180;
  int numCut = 360/cuts;
  int numSlice = 180/stacks;
  GLfloat wd;

  glPushMatrix();
  //glPolygonMode( GL_FRONT , GL_LINE); //For Wireframe sphere
  //glPolygonMode( GL_BACK, GL_LINE);

  glPolygonMode( GL_FRONT , GL_FILL);
  glPolygonMode( GL_BACK, GL_FILL);
	

  wd = (r2 - r1)/(stacks+1);
  GLfloat radiusa = r1;
  GLfloat radiusb = r2;
  GLfloat radiusc = 4.0;
  for(j=0;j<=360;j = numCut + j) // longitude
    {
      radius = r2;
      for(i=0;i<=180;i = numSlice + i, radius -= wd) // latitude
	{
	  float theta = i*DEG2RAD;
	  float theta2;
	  float phi	= j*DEG2RAD;
	  GLfloat nor[3] = { 0.0 , 0.0 , 0.0};
	  GLfloat vector1[3],vector2[3],vector3[3],vector4[3],normal[3] = {0.0 , 0.0 , 0.0};

	  if (i > 0) theta2 = (i-numSlice) * DEG2RAD;
	  else theta2 = theta;

	  // Red <- Last Blue
	  vector1[0] = radiusa*(cosf(phi)*sinf(theta2));
	  vector1[1] = radiusb*(sinf(phi)*sinf(theta2));
	  vector1[2] = radiusc*(cosf(theta2));
			
	  phi	= (j+numCut)*DEG2RAD;  
	  
	  // Yellow <- Last Green
	  vector2[0] = radiusa*(cosf(phi)*sinf(theta2));
	  vector2[1] = radiusb*(sinf(phi)*sinf(theta2));
	  vector2[2] = radiusc*(cosf(theta2));
			
	  theta = (i+numSlice)*DEG2RAD;

	  // Green
	  vector3[0] = radiusa*(cosf(phi)*sinf(theta));
	  vector3[1] = radiusb*(sinf(phi)*sinf(theta));
	  vector3[2] = radiusc*(cosf(theta));

	  phi	= j*DEG2RAD;
	  // Blue
	  vector4[0] = radiusa*(cosf(phi)*sinf(theta));
	  vector4[1] = radiusb*(sinf(phi)*sinf(theta));
	  vector4[2] = radiusc*(cosf(theta));
			
	  findNormal3Points(vector1,vector2,vector3,nor);
	  
	  glBegin(GL_TRIANGLES);
	  {
	    glColor3f(blue.r, blue.g, blue.b);
				
	    //glNormal3fv(nor);
	    glTexCoord2f(image_width(vector1), image_height(vector1));
	    glVertex3fv(vector1);
				
	    //glNormal3fv(nor);
	    glTexCoord2f(image_width(vector2), image_height(vector2));
	    glVertex3fv(vector2);

	    //glNormal3fv(nor);
	    glTexCoord2f(image_width(vector3), image_height(vector3));
	    glVertex3fv(vector3);
	  }
	  glEnd();
				
	  findNormal3Points(vector3,vector2,vector4,nor);

	  glBegin(GL_TRIANGLES);
	  {
				
	    glColor3f(blue.r, blue.g, blue.b);
	    //glNormal3fv(nor);
	    glTexCoord2f(image_width(vector1), image_height(vector1));
	    glVertex3fv(vector1);
				
	    //glNormal3fv(nor);
	    glTexCoord2f(image_width(vector4), image_height(vector4));
	    glVertex3fv(vector4);

	    //glNormal3fv(nor);
	    glTexCoord2f(image_width(vector3), image_height(vector3));
	    glVertex3fv(vector3);
	  }

	  glEnd();
	  
	}
    }
  glPopMatrix();
 glDisable(GL_TEXTURE_2D);                                   // Enable 2D texture mapping

}

void drawEye() {
  glEnable(GL_COLOR_MATERIAL);
  glPolygonMode( GL_FRONT , GL_FILL);
  glPolygonMode( GL_BACK, GL_FILL);
  // Generate an Eye
  glPushMatrix();
  glRotatef(5.0, 0.0, 1.0, 0.0);
  glRotatef(-10.0, 1.0, 0.0, 0.0);
  glTranslatef(0.0, 0.0, 4.0-0.35);
  glColor3f(black.r, black.g, black.b);
  glutSolidSphere(0.3, 20, 20);
  glPopMatrix();

  // Generate an Eye
  glPushMatrix();
  glRotatef(-5.0, 0.0, 1.0, 0.0);
  glRotatef(-10.0, 1.0, 0.0, 0.0);
  glTranslatef(0.0, 0.0, 4.0-0.35);
  glColor3f(black.r, black.g, black.b);
  glutSolidSphere(0.3, 20, 20);
  glPopMatrix();
}

void drawTail() {
  glEnable(GL_COLOR_MATERIAL);
  glPolygonMode( GL_FRONT , GL_FILL);
  glPolygonMode( GL_BACK, GL_FILL);

 glPushMatrix();
 glTranslatef(0.0, 0.0, -3);
 glBegin(GL_TRIANGLE_FAN); {
    glColor3f(red.r, red.g, red.b);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0); // v0
    glNormal3f(1.3, 0.0, 0.0);
    glColor3f(blue.r, blue.g, blue.b);
    glVertex3f(0.0, 1.0, -2.75); // v1
    glColor3f(yellow.r, yellow.g, yellow.b);
    glVertex3f(0.1, 0.6, -2.95); // v2
    glColor3f(green.r, green.g, green.b);
    glNormal3f(0.85, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -2.65); // v3
    glColor3f(yellow.r, yellow.g, yellow.b);
    glVertex3f(0.1,-0.9, -2.95); // v4
    glColor3f(green.r, green.g, green.b);
    glVertex3f(0.0, -1.5, -2.75); // v5 
  } glEnd();

  glBegin(GL_TRIANGLE_FAN); {
    glColor3f(green.r, green.g, green.b);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0); // v0
    glColor3f(yellow.r, yellow.g, yellow.b);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, -1.5, -2.75); // v1
    glColor3f(green.r, green.g, green.b);
    glVertex3f(-0.1,-0.9, -2.95); // v2
    glColor3f(red.r, red.g, red.b);
    glNormal3f(-0.85, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -2.65); // v3
    glColor3f(green.r, green.g, green.b);
    glNormal3f(-1.3, 0.0, 0.0);
    glVertex3f(-0.1, 0.6, -2.95); // v4
    glColor3f(blue.r, blue.g, blue.b);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, -2.75); // v5
  } glEnd();
  glPopMatrix();

  
}

void fish() {
  drawBody(1.0, 3.0, 50, 50);
  drawEye();
  drawTail();

}

void display(void) 
{

  glClear(GL_COLOR_BUFFER_BIT | 
	  GL_DEPTH_BUFFER_BIT);  // clear color and depth buffer

  glEnable(GL_COLOR_MATERIAL);

  glPushMatrix();
  glRotatef(R, 0.0, 1.0, 0.0);
  fish();
  glPopMatrix();
	
  glutSwapBuffers();
}

void reshape(int w, int h) 
{
  WINX = w;
  WINY = h;
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0, (GLfloat)w/(GLfloat)h, 0.1, zFAR);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xMovement, yMovement, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void specialKeys(int key, int x, int y)
{
  switch(key)
    {
    case GLUT_KEY_LEFT:
      {
	xMovement = xMovement - .1;
	reshape(WINX,WINY);
	break;
      }
    case GLUT_KEY_RIGHT:
      {
	xMovement = xMovement + .1;
	reshape(WINX,WINY);
	break;
      }
    case GLUT_KEY_UP:
      {
	yMovement = yMovement + .1;
	reshape(WINX,WINY);
	break;
      }
    case GLUT_KEY_DOWN:
      {
	yMovement = yMovement - .1;
	reshape(WINX,WINY);
	break;
      }
    }
}
void keyboard(unsigned char key, int x, int y) 
{
	
  switch(key)
    {
    case 27:
      {
	exit(0);
	break;
      }
    case 'r':
      R += 1.0;
      break;

    case '=':
      {
	zoom = zoom + 0.3;
	if(zoom >= zFAR )
	  zoom = zFAR;
	reshape(WINX,WINY);
	break;
      }
    case '-':
      {
	zoom = zoom - 0.3;
	if(zoom <= 0.0 )
	  zoom = 0.0;
	reshape(WINX,WINY);
	break;
      }
    case 'a':
      {
	xMovement = xMovement - .3;
	reshape(WINX,WINY);
	break;
      }
    case 'd':
      {
	xMovement = xMovement + .3;
	reshape(WINX,WINY);
	break;
      }
    case 'w':
      {
	yMovement = yMovement + .3;
	reshape(WINX,WINY);
	break;
      }
    case 's':
      {
	yMovement = yMovement - .3;
	reshape(WINX,WINY);
	break;
      }
    case ' ':
      {
	yMovement = 0.0; //recenter the camera
	xMovement = 0.0;
	zoom = 20.0;
	reshape(WINX,WINY);
	break;
      }
    }

  glutPostRedisplay();
}

void lighting()
{
  // Position, Ambient, Diffuse & Specular Components are Set
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
  // Enable Lighting and Hidden Surface Removal
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);  // Must be after window init & create


  glutPostRedisplay();
}
void init() 
{

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

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

}




int main(int argc,char ** argv)
{	
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WINX,WINY);
  glutInitWindowPosition(20, 50);
  glutCreateWindow("FiSh");

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  lighting();
  glutMainLoop();
  return 0;
}
