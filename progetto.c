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
static double maxTime = 1; //minutes
static time_t attackTime;
static GLfloat fogd;
struct player {
	int attack;
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
	labyrint[x][y].value = 'p';
	player.posx = labyrint[x][y].x;
	player.posy = labyrint[x][y].y;
}
void init(void) {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// enable Materials
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	// enable shadows
	glShadeModel(GL_SMOOTH);
	// enable depth
	glEnable(GL_DEPTH_TEST);
	//enable fog
	glEnable(GL_FOG);
	float FogCol[3] = { 0.35f, 0.35f, 0.35f };
	glFogfv(GL_FOG_COLOR, FogCol);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY,0.006);
	// set and enable lights
	glEnable(GL_LIGHTING);
	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 0.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	GLfloat diffuseLight[] = {0.5f, 0.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	GLfloat lightPos[] = {12.5*5, 12.5*5, 12.5*5, 2.0f };
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);
	// set and enable texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	// init Maze Wall
	freadlab();

	// init Floor cords
	initFloor();

	// init obj
	//initObj();

	// load wall texture
	initTexture();

	// random spawn player
	spawn();
	player.attack = 0;
	// init enemy
	initEnemy();
	//start game timer
	time(&startTime);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glFogf(GL_FOG_DENSITY,fogd);
	glLoadIdentity();
	gluLookAt(player.posx, player.posy, 1.5, player.posx + player.posfx,
			player.posy + player.posfy, 1.5, 0.0, 0.0, 1.0);
	glPushMatrix();
	displayFloor();
	displayRoof();
	displayWall();
	displayEnemy();
	displayObj(0.0);
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
	if ((labyrint[(int) y][(int) x].value) == '0' || (labyrint[(int) y][(int) x].value) == 'p' ) {
		return true;
	}

	return false;
}
void attack(){
	player.attack = 1;
	time(&attackTime);
	ai = (player.posy + player.posfy*1.5) / 5
			+ player.speed * sin((player.angle * pi) / 180);
	aj = (player.posx + player.posfx*1.5) / 5
			+ player.speed * cos((player.angle * pi) / 180);
	for(int i = 0; i <= 1; i++){
		for(int j = 0; j <= 1; j++){
			if(enemies[ai+i][aj+j] != -1)
			{
				enemy[enemies[ai+i][aj+j]].alive = 0;
			}
		}
	}
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
		vittoria_sfera(
				(player.posx - player.posfx) / 5
						- (player.speed - 0.1) * cos((player.angle * pi) / 180),
				(player.posy - player.posfy) / 5
						- (player.speed - 0.1)
								* sin((player.angle * pi) / 180));
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
	case 'f':
		attack();
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
	fogd = 0.006*diffTime*sin((diffTime * pi) / 180);
	movement();
	if(difftime(currentTime, attackTime)>=1.25 && player.attack == 1)
	{
		player.attack = 0;
		ai= -1;
		aj = -1;
	}
	if(stato == 1)
	{
		glutKeyboardFunc(NULL);
		printf("You Win");
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
	glDeleteTextures(N_Texture,textures);
	return 0;
}
