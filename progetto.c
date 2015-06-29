/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *  Author: Chiara
 *  Modifier: Antonio 20/giu/2015
 */

#include <GL/glut.h>
#include "utils/tga.h"
#include <math.h>
#include "pavimento.h"
#include "LabReader.h"

static GLdouble pi = 3.14159;
static GLdouble angle = 0.0;
static GLdouble posx = 10.0;
static GLdouble posy = 10.0;
static GLdouble posfx = 1.0;
static GLdouble posfy = 0.0;

void init(void) {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	// set lights

	GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lightPos[] = { 200.f, 200.0f, 200.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	// enabling texture
	glEnable(GL_TEXTURE_2D);

	freadlab();

	int x = 2.5, y = 2.5;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			labyrint[i][j].x = x;
			labyrint[i][j].y = y;
			x += 5;
		}
		y += 5;
	}

	GLubyte *pBytes;
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
	pBytes = gltLoadTGA("./assets/Stone.tga", &iWidth, &iHeight, &iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.1, 0.1, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posx, posy, 1.5, posx + posfx, posy + posfy, 1.5, 0.0, 0.0, 1.0);

	glPushMatrix();
	displayFloor();
	displayRoof();
	displayWall();
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
		posx = posx + cos((angle * pi) / 180);// speed * cos -> change player walk speed
		posy = posy + sin((angle * pi) / 180);	// the same as above with sin
		break;
	case 's':
		posx = posx - cos((angle * pi) / 180);				// as for 'w'
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
void timer(int t) {
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
	//glutTimerFunc(15,timer,15);
	glutMainLoop();
	return 0;
}
