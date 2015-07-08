#ifndef NEMICI_H_
#define NEMICI_H_

#include "pavimento.h"

struct enemy {
	GLdouble angle;
	GLdouble speed;
	GLdouble posx;
	GLdouble posy;
	GLdouble posfx;
	GLdouble posfy;
} enemy;

static int matrix[width][height];

void iniz();

GLdouble xavanti();
GLdouble yavanti();

GLdouble xindietro();
GLdouble yindietro();

void movement();


#endif
