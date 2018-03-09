#ifndef SMILE_H
#define SMILE_H

#include "colors.h"

class Sun: public Drawable {
    public:
    void render(float time) {
      GLfloat emit[] = {red.r, red.g, red.b, 1};
//      GLfloat emit[] = {1, 1, 1, 1};
      glPushMatrix();                   // Sun
          glMaterialfv(GL_FRONT_AND_BACK,
                   GL_EMISSION, emit);
          materialColor(sun);
          glutSolidSphere(0.73, 20, 16);
          emit[0] = 0.0;
          emit[1] = 0.0;
          emit[2] = 0.0;
          glMaterialfv(GL_FRONT_AND_BACK,
                   GL_EMISSION, emit); // Reset Emission
      glPopMatrix();

      int step = 360 / 15;
      for(int i = 0; i < 360; i += step) {
        glPushMatrix();
            float height = 2;
            if(i % (step * 2) == 0) {
                height = 1.5;
            }
            glRotatef(90, 1, 0, 0);
            glRotatef(i, 0, 1, 0);
            materialColor(sunRay);
            float random = (rand() % 100) / 100.0;
//            height = random * 1.5;
            glutSolidCone(.2, height, 20, 16);
        glPopMatrix();
      }
    }
};

class SurpriseFace : public Drawable {
    public:
    void render(float time) {
        // draw head
        materialColor(yellowFace);
        glutSolidSphere(.5, 20, 16);

        // draw eyes
        float x = .25;
        float y = .1;
        float z = .5;
        float size = .15;

        glPushMatrix();                             // Save Matrixes
            glTranslatef(x, y, z);
            materialColor(eye);
            glutSolidSphere(size, 20, 16);
            glPushMatrix();
                glTranslatef(0, 0, size);
                materialColor(pupil);
                glutSolidSphere(.07, 20, 16);
            glPopMatrix();
        glPopMatrix();                              // Restore Matrixes
        glPushMatrix();                             // Save Matrixes
            glTranslatef(-x, y, z);
            materialColor(eye);
            glutSolidSphere(size, 20, 16);
            glPushMatrix();
                glTranslatef(0, 0, size);
                materialColor(pupil);
                glutSolidSphere(.07, 20, 16);
            glPopMatrix();
        glPopMatrix();                              // Restore Matrixes

        // draw mouth
        glPushMatrix();
        glTranslatef(0, -.2, .5);
        materialColor(pupil);
        glutSolidSphere(.1, 20, 16);
        glPopMatrix();

    }
};

class AngelFace : public Drawable {
    public:
    void render(float time) {
        // draw head
        materialColor(yellowFace);
        glutSolidSphere(.5, 20, 16);

        // draw eyes
        float x = .25;
        float y = .1;
        float z = .5;
        float size = .15;

        glPushMatrix();                             // Save Matrixes
            glTranslatef(x, y, z);
            materialColor(eye);
            glutSolidSphere(size, 20, 16);
            glPushMatrix();
                glTranslatef(0, 0, size);
                materialColor(pupil);
                glutSolidSphere(.07, 20, 16);
            glPopMatrix();
        glPopMatrix();                              // Restore Matrixes
        glPushMatrix();                             // Save Matrixes
            glTranslatef(-x, y, z);
            materialColor(eye);
            glutSolidSphere(size, 20, 16);
            glPushMatrix();
                glTranslatef(0, 0, size);
                materialColor(pupil);
                glutSolidSphere(.07, 20, 16);
            glPopMatrix();
        glPopMatrix();                              // Restore Matrixes

		// draw halo
		glPushMatrix();
			glTranslatef(0, .7, 0);
			glRotatef(90, 1, 0, 0);
			glScalef(1, 1, .25);
			materialColor(eye);
			glutSolidTorus(.3, .5, 30, 30);
		glPopMatrix();
        // draw mouth
        glPushMatrix();
        glTranslatef(0, -.2, .5);
        materialColor(pupil);
        glutSolidSphere(.1, 20, 16);
        glPopMatrix();

    }
};

class AngryFace : public Drawable {
    public:
    void render(float time) {
        // draw head
        materialColor(madFace);
        glutSolidSphere(.5, 20, 16);

        // draw eyes
        float x = .25;
        float y = .1;
        float z = .5;
        float size = .15;

        glPushMatrix();                             // Save Matrixes
            glTranslatef(x, y, z);
            materialColor(eye);
            glutSolidSphere(size, 20, 16);
            glPushMatrix();
                glTranslatef(0, 0, size);
                materialColor(pupil);
                glutSolidSphere(.07, 20, 16);
            glPopMatrix();
        glPopMatrix();                              // Restore Matrixes
        glPushMatrix();                             // Save Matrixes
            glTranslatef(-x, y, z);
            materialColor(eye);
            glutSolidSphere(size, 20, 16);
            glPushMatrix();
                glTranslatef(0, 0, size);
                materialColor(pupil);
                glutSolidSphere(.07, 20, 16);
            glPopMatrix();
        glPopMatrix();                              // Restore Matrixes

        // draw mouth
        glPushMatrix();
        glTranslatef(0, -.2, .5);
        materialColor(pupil);
        glutSolidSphere(.1, 20, 16);
        glPopMatrix();

    }
};

class DevilFace : public Drawable {
    public:
    void render(float time) {
        float headRadius = .5;
        // draw head
        materialColor(devilFace);
        glutSolidSphere(.5, 20, 16);

        // draw eyes
        float x = .25;
        float y = .1;
        float z = .5;
        float size = .15;
        Color color = white;

        glPushMatrix();                             // Save Matrixes
            glTranslatef(x, y, z);
            materialColor(eye);
            glutSolidSphere(size, 20, 16);
            glPushMatrix();
                glTranslatef(0, 0, size);
                materialColor(pupil);
                glutSolidSphere(.07, 20, 16);
            glPopMatrix();
        glPopMatrix();                              // Restore Matrixes
        glPushMatrix();                             // Save Matrixes
            glTranslatef(-x, y, z);
            materialColor(eye);
            glutSolidSphere(size, 20, 16);
            glPushMatrix();
                glTranslatef(0, 0, size);
                materialColor(pupil);
                glutSolidSphere(.07, 20, 16);
            glPopMatrix();
        glPopMatrix();                              // Restore Matrixes

        // draw mouth
        glPushMatrix();
        glTranslatef(0, -.2, .5);
        materialColor(pupil);
        glutSolidSphere(.1, 20, 16);
        glPopMatrix();

        // draw horns
        glPushMatrix();
            glTranslatef(headRadius * cos(M_PI / 4.0), headRadius * sin(M_PI / 4.0), 0);
            glRotatef(-90, 1, 0, 0);
            glRotatef(45, 0, 1, 0);
            materialColor(devilFace);
            glutSolidCone(.15, .45, 20, 16);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-headRadius * cos(M_PI / 4.0), headRadius * sin(M_PI / 4.0), 0);
            glRotatef(-90, 1, 0, 0);
            glRotatef(-45, 0, 1, 0);
            materialColor(devilFace);
            glutSolidCone(.15, .45, 20, 16);
        glPopMatrix();

    }
};

#endif
