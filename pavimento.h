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

#endif /* PAVIMENTO_H_ */
