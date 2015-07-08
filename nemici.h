#ifndef NEMICI_H_
#define NEMICI_H_

#include <math.h>
#define _USE_MATH_DEFINES
#include "pavimento.h"

struct enemy {
	int alive;
	int step;
	int currentstep;
	GLdouble angle;
	GLdouble speed;
	GLdouble posx;
	GLdouble posy;
}enemy[5];

int enemies[width][height];

void initEnemy();
void setEnemyCords(GLdouble x,GLdouble y,int i);
void displayEnemy();

void movement();


#endif
