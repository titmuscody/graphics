#ifndef FISH_H
#define FISH_H

#include "math.h"

#include "colors.h"
#include "wall.h"
#include "enemy.h"

using std::vector;

class Fish: public Drawable {
	public:
		void render(float time) override {
			anim_time += time;
			if(anim_time > 2) {
				anim_time -= 2;
			}
			glPushMatrix();
				glTranslatef(loc.x, loc.y, loc.z);
				glRotatef(rot, rotPoint.x, rotPoint.y, rotPoint.z);
				drawBody(1.0, 3.0, 15, 15);
				drawEye();
				//draw tail
				glPushMatrix();
					glTranslatef(0.0, 0.0, -3);
					drawTail(anim_time / 2.0f);
				glPopMatrix();
				//draw right fin
				glPushMatrix();
					glTranslatef(1.2, 0.5, 0.0);
					glScalef(1, 0.5, 1);
					drawTail(anim_time / 2.0f);
				glPopMatrix();
				//draw left fin
				glPushMatrix();
					glTranslatef(-1.2, 0.5, 0.0);
					glRotatef(180, 0, 0, 1);
					glScalef(1, 0.5, 1);
					drawTail(anim_time / 2.0f);
				glPopMatrix();
			glPopMatrix();
    }
		void lookat(Point here) {
			Point looking = (here - loc).unitVector();
			Point start = Point(0, 0, 1);
			rotPoint = start.cross(looking);
			rot = (180 / M_PI) * acos(Point::dot(start, looking));
		}
		void setPos(Point here) {
			loc = here;
		}
		Fish(GLuint tex) {
			scaleTex = tex;
		}
		void updateDir(vector<Fish*> fishes, vector<Wall*> walls, vector<Enemy*> enemies) {
			Point last_dir = dir;
			
			for(int i = 0; i < walls.size(); ++i) {
				Wall wall = *walls[i];
				float dist = Point::dot(wall.dir, loc - wall.loc);
				if(dist < 15) {
					float power =  1.0 / pow(dist, 1);
					if(repel) {
						last_dir = last_dir + (power * wall.dir);
					} else {
						last_dir = last_dir + (.15 * power * wall.dir);
					}
				}
			}
			for(int i = 0; i < fishes.size(); ++i) {
				Fish* cur = fishes[i];
				if(cur == this)
					continue;
				float dist = (loc - cur->loc).size();
				if(repel) {
					Point goto_here = loc - cur->loc;
					last_dir = last_dir + (.000001 * goto_here);
				} else if(dist < 6) {
					float power =  1.0 / pow(dist, 3);
					Point goto_here = loc - cur->loc;
					last_dir = last_dir + (power * .01 * goto_here);
				} else if(dist < 8) {
					last_dir = last_dir + (.01 * cur->dir);
				}
			}
			for(int i = 0; i < enemies.size(); ++i) {
				Enemy* cur = enemies[i];
				float dist = (loc - cur->loc).size() - cur->radius;
				if(dist < 20) {
					float power =  1.0 / pow(dist, 4);
					Point goto_here = loc - cur->loc;
					last_dir = last_dir + (power * goto_here);
				}
			}

			this->dir = last_dir.unitVector();
		}
		void move() override {
			Point dest = loc + (speed * dir);
			lookat(dest);
			setPos(dest);
		}
		void repulse() {
			repel = !repel;
		}
		Point dir = Point(0.001, .00001, -1).unitVector();
	private:
		GLuint scaleTex;
		GLfloat rot;
		Point rotPoint;
		Point loc;
		float speed = .2;
		bool repel = false;
		float anim_time = 0;
		void drawTail(float done) {
			float x_offset;
			float z_offset;
			if(done > .5) {
				x_offset = cos((1 - done) * 2 * M_PI);
				z_offset = sin((1 - done) * 2 * M_PI);
			} else {
				x_offset = cos(done * 2 * M_PI);
				z_offset = sin(done * 2 * M_PI);
			}

			glEnable(GL_COLOR_MATERIAL);
			glPolygonMode( GL_FRONT , GL_FILL);
			glPolygonMode( GL_BACK, GL_FILL);

			glBegin(GL_TRIANGLE_FAN); {
				vertexColor(red);
				glNormal3f(1.0, 0.0, 0.0);
				glVertex3f(0.0, 0.0, 0.0); // v0

				vertexColor(blue);
				glNormal3f(1.3, 0.0, 0.0);
				glVertex3f(0.0 + x_offset, 1.0, -2.75 + z_offset); // v1

				vertexColor(yellow);
				glVertex3f(0.1 + x_offset, 0.6, -2.95 + z_offset); // v2

				vertexColor(green);
				glNormal3f(0.85, 0.0, 0.0);
				glVertex3f(0.0 + x_offset, 0.0, -2.65 + z_offset); // v3

				vertexColor(yellow);
				glVertex3f(0.1 + x_offset,-0.9, -2.95 + z_offset); // v4

				vertexColor(green);
				glVertex3f(0.0 + x_offset, -1.5, -2.75 + z_offset); // v5 
			} glEnd();
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

		GLfloat image_height(GLfloat vector[]) {
			return vector[1] / 2.0;
		}
		GLfloat image_width(GLfloat vector[]) {
			return -vector[2] / 2.0;
		}

		void drawBody(GLfloat r1, GLfloat r2, int cuts, int stacks)
		{

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
				
					
				//findNormal3Points(vector1,vector2,vector3,nor);
				
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
						
				//findNormal3Points(vector3,vector2,vector4,nor);

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
						
				//findNormal3Points(vector3,vector2,vector4,nor);

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
};
#endif
