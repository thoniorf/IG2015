/*
 * proj2015.c
 *
 *  Created on: Jun 18, 2015
 *      Author: thoniorf
 */
#include <GL/glut.h>
#include "utils/tga.h"
#include "utils/utils.h"

const int t = 15;

static GLdouble pi = 3.14159;
static GLdouble angle = 0.0;
static GLdouble posx = 0.0;
static GLdouble posy = 0.0;
static GLdouble posfx = 1.0;
static GLdouble posfy = 0.0;

void displayFloor() {
	GLboolean odd = 0;
	GLint n_quads = 20;
	glPushMatrix();
	for (int i = 0; i < n_quads; i++) {
		if(odd){
			odd = 0;
		} else {
			odd= 1;
		}
		glPushMatrix();
		for (int j = 0; j < n_quads; j++) {
			if (odd) {
				glColor3f(0.1, 0.1, 1);
				odd = 0;
			} else {
				glColor3f(0.1, 0.0, 0.45);
				odd = 1;
			}
			glBegin(GL_QUADS);
			glVertex2f(0.0, 0.0);
			glVertex2f(5., 0.0);
			glVertex2f(5., 5.);
			glVertex2f(0.0, 5.);
			glEnd();
			glTranslatef(5., 0.0, 0.0);
		}
		glPopMatrix();
		glTranslatef(0.0,5.,0.0);
	}
	glPopMatrix();
	glFlush();

}

void displayObjs(){

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(45.0,25.0,0.0);
	glScalef(1.0,1.0,3.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, .25, 0.1);
	glTranslatef(25.,50.0,0.0);
	glutSolidSphere(3.0,10,5);
	glPopMatrix();

}
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	GLfloat ambientLight[] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat lightPos[] = { 50.f, 50.0f, 50.0f, 50.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posx, posy, 1.5, posx + posfx, posy + posfy, 1.5, 0.0, 0.0, 1.0);
	displayFloor();
	displayObjs();
	glutSwapBuffers();

}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLfloat) w / (GLfloat) h, 0.5, 200.0);

}

void keyboard(unsigned char key, int x, int y) {

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
	return 0;
}
