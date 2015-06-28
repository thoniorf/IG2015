/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *  Author: Chiara
 *  Modifier: Antonio 20/giu/2015
 */

#include <GL/glut.h>
#include <math.h>
#include "pavimento.h"

void initWall(int i, char buf[width+1]){
	for(int j = 0; j < width; j++){
		labyrint[i][j].value = buf[j];
	}
}
void displayWall() {
	glPushMatrix();
	glTranslatef(2.5, 2.5, 0.0);
	for (int i = 0; i < width; i++) {

		glPushMatrix();
		for (int j = 0; j < height; j++) {
			if (labyrint[i][j].value == '1') {
				glColor3f(0.8f, 0.33f, 0.12f);
				//usare i vertici !!
				glutSolidCube(5);
			}
			glTranslatef(5.0, 0.0, 0.0);
		}

		glPopMatrix();
		glTranslatef(0.0, 5.0, 0.0);

	}
	glPopMatrix();
}

void displayFloor() {

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

void displayRoof() {

	glColor3f(1.0, 0.28, 0.28);

	glPushMatrix();
	glTranslatef(0.0,0.0,2.5);
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

