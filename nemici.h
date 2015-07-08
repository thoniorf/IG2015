#ifndef NEMICI_H_
#define NEMICI_H_

#include <math.h>
#include <stdlib.h>
#include "pavimento.h"

struct enemy {
	int alive;
	int step;
	int currentstep;
	GLdouble angle;
	GLdouble speed;
	GLdouble posx;
	GLdouble posy;
}enemy[6];

int enemies[width][height];

void initEnemy();
void setEnemyCords(GLdouble x,GLdouble y,int i);
void displayEnemy();

void movement();


#endif
