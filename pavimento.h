/*
 * pavimento.h
 *
 *  Created on: Jun 19, 2015
 *      Author: Antonio
 */

#ifndef PAVIMENTO_H_
#define PAVIMENTO_H_

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "utils/tga.h"

#define width 25				// Maze columns
#define height 25				// Maze rows

#define N_Texture 3				// Texture number
#define Wall 0					// Wall texture index
#define Floor 1					// Floor
#define Roof 2					// Roof

static GLuint textures[N_Texture];
static const char *uv_file_name[N_Texture] = {"./assets/Wall.tga","./assets/Floor.tga","./assets/Roof.tga"};

static float exitangle=0.0;

static float lato=1.0;//lato del cubo
static float raggio=0.2;//raggio della sfera
static int ai,aj;
static int stato=0;//stato del gioco



struct Cords
{
	GLdouble x ;
	GLdouble y ;
	char value;
}labyrint[width][height];

struct Uv {
	GLubyte *pBytes;
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
}uv;

void initWall(int i, char buf[width+1]);
void initFloor();
void initTexture();
void displayWall();
void displayFloor();
void displayRoof();
void vittoria_sfera(double x, double y);

static void drawBox(GLfloat size, GLenum type) {
	static GLfloat n[6][3] = { { -1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 1.0,
			0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, 0.0, -1.0 },
			{ 0.0, 0.0, 1.0 } };
	static GLint faces[6][4] = { { 0, 1, 2, 3 }, { 3, 2, 6, 7 }, { 7, 6, 5, 4 },
			{ 4, 5, 1, 0 }, { 5, 6, 2, 1 }, { 7, 4, 0, 3 } };
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);

		glTexCoord3f(1.0, 1.0, -1.0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord3f(1.0, -1.0, -1.0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord3f(-1.0, -1.0, -1.0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord3f(-1.0, 1.0, -1.0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}
#endif /* PAVIMENTO_H_ */
