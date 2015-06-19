/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *  Author: Chiara
 *  Modifier: Antonio 19/giu/2015
 */

#include <GL/glut.h>
#include <math.h>
#include "pavimento.h"

static GLdouble pi = 3.14159;
static GLdouble angle = 0.0;
static GLdouble posx = 0.0;
static GLdouble posy = 0.0;
static GLdouble posfx = 1.0;
static GLdouble posfy = 0.0;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	int i, j;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++)
			labyrint[i][j].x = 0;
			labyrint[i][j].y = 0;
			labyrint[i][j].value = 0;
	}

	for (i = 0; i < width; i++) {
		labyrint[0][i].value = 1;
		labyrint[24][i].value = 1;
		labyrint[i][0].value = 1;
		labyrint[i][24].value = 1;

	}
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.1, 0.1, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posx, posy, 1.5, posx + posfx, posy + posfy, 1.5, 0.0, 0.0, 1.0);

	glPushMatrix();

	displayPav();
	displayMura();
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 500.0);

}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		angle += 2.0;
		posfx = cos((angle * pi) / 180);
		posfy = sin((angle * pi) / 180);
		break;
	case 'd':
		angle -= 2.0;
		posfx = cos((angle * pi) / 180);
		posfy = sin((angle * pi) / 180);
		break;
	case 'w':
		posx = posx + cos((angle * pi) / 180);
		posy = posy + sin((angle * pi) / 180);
		break;
	case 's':
		posx = posx - cos((angle * pi) / 180);
		posy = posy - sin((angle * pi) / 180);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
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
