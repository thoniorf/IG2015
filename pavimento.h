/*
 * pavimento.h
 *
 *  Created on: Jun 19, 2015
 *      Author: Antonio
 *      Modifier: Antonio 20/giu/2015
 */

#ifndef PAVIMENTO_H_
#define PAVIMENTO_H_

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "utils/tga.h"

#define width 25
#define height 25

struct Cords
{
	float x ;
	float y ;
	char value;
}labyrint[width][height];

struct texture {
	GLubyte *pBytes;
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
}uvWall;

void initWall(int i, char buf[width+1]);
void initWallTexture();
void displayWall();
void displayFloor();
void displayRoof();

#endif /* PAVIMENTO_H_ */
