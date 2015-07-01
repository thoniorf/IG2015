/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *  Author: Chiara
 *  Modifier: Antonio 20/giu/2015
 */

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "utils/tga.h"
#include "pavimento.h"
#include "LabReader.h"

static GLdouble pi = 3.14159;
static time_t startTime;
static time_t currentTime;
static double diffTime;
static double maxTime = 1; //minutes

struct player {
	GLdouble angle;
	GLdouble posx;
	GLdouble posy;
	GLdouble posfx;
	GLdouble posfy;
}player;

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

	// set and enable texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	// read maze from file
	freadlab();

	// inizialize floor coords
	int x = 2.5, y = 2.5;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			labyrint[i][j].x = x;
			labyrint[i][j].y = y;
			x += 5;
		}
		y += 5;
	}

	// load wall texture
	initWallTexture();

	// inizialize player
	player.angle = 0.0;
	player.posx = 10.0;
	player.posy = 10.0;
	player.posfx = 1.0;
	player.posfy = 0.0;

	//start game timer
	time(&startTime);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.1, 0.1, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(player.posx, player.posy, 1.5, player.posx + player.posfx, player.posy + player.posfy, 1.5, 0.0, 0.0, 1.0);

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
		player.angle += 2.0;
		player.posfx = cos((player.angle * pi) / 180);
		player.posfy = sin((player.angle * pi) / 180);
		break;
	case 'd':
		player.angle -= 2.0;
		player.posfx = cos((player.angle * pi) / 180);
		player.posfy = sin((player.angle * pi) / 180);
		break;
	case 'w':
		player.posx = player.posx + cos((player.angle * pi) / 180);// speed * cos -> change player walk speed
		player.posy = player.posy + sin((player.angle * pi) / 180);	// the same as above with sin
		break;
	case 's':
		player.posx = player.posx - cos((player.angle * pi) / 180);				// as for 'w'
		player.posy = player.posy - sin((player.angle * pi) / 180);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void idle(){
	time(&currentTime);
	diffTime = difftime(currentTime,startTime);
	if(diffTime >= maxTime*60)
	{
		printf("Time Over");
		exit(0);
	}
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
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
