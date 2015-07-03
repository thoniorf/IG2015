/*
 * ObjLoader.h
 *
 *  Created on: Jul 1, 2015
 *      Author: thoniorf
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "utils/tga.h"

struct face {
	int x1,t1,n1;
	int x2,t2,n2;
	int x3,t3,n3;
};

void loadObj();
void displayObj();

#endif /* OBJLOADER_H_ */
