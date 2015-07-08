/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *  Author: Chiara
 *  Modifier: Antonio 20/giu/2015
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "utils/tga.h"
#include "pavimento.h"
#include "LabReader.h"
#include "nemici.h"
#include "ObjLoader.h"

GLdouble pi = 3.14159;
static time_t startTime;
static time_t currentTime;
static double diffTime;
static double maxTime = 15; //minutes

struct player {
	GLdouble angle;
	GLdouble speed;
	GLdouble posx;
	GLdouble posy;
	GLdouble posfx;
	GLdouble posfy;
} player;

void spawn() {
	int x, y;
	// inizialize player
	player.speed = 0.25;
	player.angle = 0.0;
	player.posfx = 1.0;
	player.posfy = 0.0;

	x = rand() % 24 + 1;
	y = rand() % 24 + 1;

	while (labyrint[y][x].value != '0') {
		x = rand() % 2 - 1;
		y = rand() % 2 - 1;
		if (x > width || x < 0)
			x = rand() % 24 + 1;
		if (y > height || y < 0)
			y = rand() % 24 + 1;
	}
	player.posx = labyrint[x][y].x;
	player.posy = labyrint[x][y].y;
}
void init(void) {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	// enable Materials
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// enable shadows
	glShadeModel(GL_SMOOTH);
	// enable depth
	glEnable(GL_DEPTH_TEST);
	//enable fog
	//glEnable(GL_FOG);
	float FogCol[3] = { 0.35f, 0.35f, 0.35f };
	glFogfv(GL_FOG_COLOR, FogCol);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.35f);
	// set and enable lights
	glEnable(GL_LIGHTING);
	GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 0.2f };
	GLfloat lightPos[] = { 12.5*5, 12.5*5, 12.5*5, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	// set and enable texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	// init Maze Wall
	freadlab();

	// init Floor cords
	initFloor();

	// load wall texture
	initTexture();

	// random spawn player
	spawn();

	// init enemy
	initEnemy();
	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 25; j++)
		{
			printf("%i ",enemies[i][j]);
		}
		printf("\n");

	}
	printf("\n\n");
	//start game timer
	time(&startTime);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(player.posx, player.posy, 1.5, player.posx + player.posfx,
			player.posy + player.posfy, 1.5, 0.0, 0.0, 1.0);

	glPushMatrix();
	displayFloor();
	displayRoof();
	displayWall();
	displayEnemy();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 500.0);

}

bool enemycollision(double x, double y)
{
	if(enemies[(int)y][(int)x] != -1) {
			return true;
	}
	return false;

}
bool notcollisioni(double x, double y) {
	if ((labyrint[(int) y][(int) x].value) == '0') {
		return true;
	}

	return true;
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
		vittoria_sfera(
				(player.posx + player.posfx) / 5
						+ player.speed * cos((player.angle * pi) / 180),
				(player.posy + player.posfy) / 5
						+ player.speed * sin((player.angle * pi) / 180));
	if(enemycollision(
			(player.posx + player.posfx) / 5
					+ player.speed * cos((player.angle * pi) / 180),
			(player.posy + player.posfy) / 5
					+ player.speed * sin((player.angle * pi) / 180)))
		stato = 2;
	if (!notcollisioni(
				(player.posx + player.posfx) / 5
						+ player.speed * cos((player.angle * pi) / 180),
				(player.posy + player.posfy) / 5
						+ player.speed * sin((player.angle * pi) / 180)))
			break;
		player.posx = player.posx
				+ player.speed * cos((player.angle * pi) / 180);
		player.posy = player.posy
				+ player.speed * sin((player.angle * pi) / 180);
		break;
	case 's':

		if (!notcollisioni(
				(player.posx - player.posfx) / 5
						- (player.speed - 0.1) * cos((player.angle * pi) / 180),
				(player.posy - player.posfy) / 5
						- (player.speed - 0.1)
								* sin((player.angle * pi) / 180)))
			break;
		player.posx = player.posx
				- (player.speed - 0.1) * cos((player.angle * pi) / 180); // as for 'w'
		player.posy = player.posy
				- (player.speed - 0.1) * sin((player.angle * pi) / 180);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void idle() {
	time(&currentTime);
	diffTime = difftime(currentTime, startTime);
	movement();
	if(stato == 1)
	{
		printf("You Win");
		exit(0);
	}
	if(stato == 2)
	{
		printf("Game Over");
		exit(0);
	}
	if (diffTime >= maxTime * 60) {
		printf("Time Over");
		exit(0);
	}
	glutPostRedisplay();
}
void timer(int t) {

}
int main(int argc, char** argv) {
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1, timer, 5);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}
