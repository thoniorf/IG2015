#ifndef NEMICI_H_
#define NEMICI_H_

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

static int enemies[width][height];

void iniz();
void ranAngle();
void setEnemyCords(GLdouble x,GLdouble y,int i);
void displayEnemy();

void movement();


#endif
