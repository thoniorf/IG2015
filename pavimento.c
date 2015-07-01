/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *  Author: Chiara
 *
 */

#include "pavimento.h"

static void drawBox(GLfloat size, GLenum type){
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
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

    glTexCoord3f(1.0,1.0,-1.0);
    glVertex3fv(&v[faces[i][0]][0]);
    glTexCoord3f(1.0,-1.0,-1.0);
    glVertex3fv(&v[faces[i][1]][0]);
    glTexCoord3f(-1.0,-1.0,-1.0);
    glVertex3fv(&v[faces[i][2]][0]);
    glTexCoord3f(-1.0,1.0,-1.0);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

void initWall(int i, char buf[width+1]){
	for(int j = 0; j < width; j++){
		labyrint[i][j].value = buf[j];
	}

}
void initWallTexture(){
	uvWall.pBytes = gltLoadTGA("./assets/Wall.tga", &uvWall.iWidth, &uvWall.iHeight, &uvWall.iComponents, &uvWall.eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, uvWall.iComponents, uvWall.iWidth, uvWall.iHeight, 0, uvWall.eFormat, GL_UNSIGNED_BYTE, uvWall.pBytes);
	free(uvWall.pBytes);
}
void displayWall() {
	glColor3f(0.8f, 0.33f, 0.12f);
	glTranslatef(2.5,2.5,0.0);
	glPushMatrix();
	for (int i = 0; i < width; i++) {
		glPushMatrix();
		for (int j = 0; j < height; j++) {
			if (labyrint[i][j].value == '1') {
				drawBox(5,GL_QUADS);
			}
			glTranslatef(5., 0.0, 0.0);
		}
		glPopMatrix();
		glTranslatef(0.0, 5., 0.0);

	}
	glPopMatrix();
	glFlush();
}

void displayFloor() {
	glColor3f(0.1, 0.1, 1);
	glPushMatrix();
	for (int i = 0; i < width; i++) {
		glPushMatrix();
		for (int j = 0; j < height; j++) {
			glBegin(GL_QUADS);
			glVertex2f(0.0, 0.0);
			glVertex2f(5., 0.0);
			glVertex2f(5., 5.);
			glVertex2f(0.0, 5.);
			glEnd();
			glTranslatef(5., 0.0, 0.0);
		}
		glPopMatrix();
		glTranslatef(0.0, 5., 0.0);
	}
	glPopMatrix();
	glFlush();
}

void displayRoof() {

	glColor3f(1.0, 0.28, 0.28);

	glPushMatrix();
	glTranslatef(0.0,0.0,2.5);
	for (int i = 0; i < width; i++) {

		glPushMatrix();
		for (int j = 0; j < height; j++) {

			glBegin(GL_QUADS);
			glVertex2f(0.0, 0.0);
			glVertex2f(5., 0.0);
			glVertex2f(5., 5.);
			glVertex2f(0.0, 5.);
			glEnd();
			glTranslatef(5., 0.0, 0.0);
		}
		glPopMatrix();
		glTranslatef(0.0, 5., 0.0);
	}

	glPopMatrix();
	glFlush();
}

