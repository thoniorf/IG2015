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

#define N_Texture 2
#define Wall 0
#define Floor 1

static GLuint textures[N_Texture];
static const char *uv_file_name[N_Texture] = {"./assets/Wall.tga","./assets/Floor.tga"};

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
void initTexture();
void displayWall();
void displayFloor();
void displayRoof();

#endif /* PAVIMENTO_H_ */
