/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *  Author: Chiara
 *  Modifier: Antonio 19/giu/2015
 */

#include <GL/glut.h>
#include <math.h>

void displayMura( int width, int height, int wall[][width]) {
	glPushMatrix();
	glTranslatef(2.5, 2.5, 0.0);
	for (int i = 0; i < width; i++) {

		glPushMatrix();
		for (int j = 0; j < height; j++) {
			if (wall[i][j] == 1) {
				glColor3f(1.0f, 0.0f, 1.0f);
				glutSolidCube(5);
			}
			glTranslatef(5.0, 0.0, 0.0);
		}

		glPopMatrix();
		glTranslatef(0.0, 5.0, 0.0);

	}
	glPopMatrix();
}

void displayPav(int width, int height) {

	glColor3f(0.1, 0.1, 1);

	glPushMatrix();
	for (int i = 0; i < width; i++) {

		glPushMatrix();
		for (int j = 0; j < height; j++) {

			glBegin(GL_QUADS);
			glVertex2f(0.0, 0.0);
			glVertex2f(5., 0.0);
			glVertex2f(5., 5.);
			glVertex2f(0.0, 5.);
			glEnd();
			glTranslatef(5., 0.0, 0.0);
		}
		glPopMatrix();
		glTranslatef(0.0, 5., 0.0);
	}

	glPopMatrix();
	glFlush();
}

