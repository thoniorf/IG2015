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
#include <string.h>
#include <stdbool.h>
#include "utils/tga.h"
#include "utils/utils.h"

#define N_OBJ 1
#define ghost "./assets/ghost/Ghost.obj"
#define uv1 "./assets/ghost/texture.tga"
#define uv2 "./assets/ghost/texture.tga"
#define uv3 "./assets/ghost/texture.tga"
#define uv4 "./assets/ghost/texture.tga"


static GLTVector3 *vertex,*normal,*tx;
static int N_vertex,N_normal,N_tx,N_faces;

struct face {
	int x1,t1,n1;
	int x2,t2,n2;
	int x3,t3,n3;
}*faces;
void initObj();
bool readN(char c,int pos,int *N_c);
bool loadObj();
void displayObj(GLfloat scale);

#endif /* OBJLOADER_H_ */
