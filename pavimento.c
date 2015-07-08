/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *  Author: Chiara
 *
 */

#include "pavimento.h"

static void drawBox(GLfloat size, GLenum type) {
	static GLfloat n[6][3] = { { -1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 1.0,
			0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, 0.0, 1.0 },
			{ 0.0, 0.0, -1.0 } };
	static GLint faces[6][4] = { { 0, 1, 2, 3 }, { 3, 2, 6, 7 }, { 7, 6, 5, 4 },
			{ 4, 5, 1, 0 }, { 5, 6, 2, 1 }, { 7, 4, 0, 3 } };
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

		glTexCoord3f(1.0, 1.0, -1.0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord3f(1.0, -1.0, -1.0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord3f(-1.0, -1.0, -1.0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord3f(-1.0, 1.0, -1.0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void initWall(int i, char buf[width + 1]) {
	for (int j = 0; j < width; j++) {
		labyrint[i][j].value = buf[j];
	}

}
void initFloor() {
	int x = 2.5, y = 2.5;
	for (int i = 0; i < width; i++) {
		y = 2.5;
		for (int j = 0; j < height; j++) {
			labyrint[i][j].x = x;
			labyrint[i][j].y = y;
			y += 5.;
		}
		x += 5.;
	}
}
void initTexture() {
	glGenTextures(N_Texture, textures);
	for (int i = 0; i < N_Texture; i++) {
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		uv.pBytes = gltLoadTGA(uv_file_name[i], &uv.iWidth, &uv.iHeight,
				&uv.iComponents, &uv.eFormat);
		glTexImage2D(GL_TEXTURE_2D, 0, uv.iComponents, uv.iWidth, uv.iHeight, 0,
				uv.eFormat, GL_UNSIGNED_BYTE, uv.pBytes);
		free(uv.pBytes);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
}

//funzione per far apparire la sfera al posto del quadrato
void vittoria_sfera(double x, double y) {
	if ((labyrint[(int) y][(int) x].value) == 'e') {
		stato = 1;
		glutIdleFunc(NULL);
		glutKeyboardFunc(NULL);
	}
}

void displayExit() {
	double tmp;
	//if per far girare il cubo (se supera i 360 gradi,torna a 0, altrimenti si incrementa di 25gradi)
	exitangle = (exitangle >= 360) ? 0 : exitangle + 5;
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.25);
	glRotatef(exitangle, 0.0, 0.0, 1.0);
	if (stato == 1) {
		tmp = raggio;
		raggio = lato;
		lato = tmp;
	}

	//glBindTexture(GL_TEXTURE_2D, textures[Wall]);
	drawBox(lato, GL_QUADS);
	glutSolidSphere(raggio, 8.0, 8.0);
	glPopMatrix();

}

void displayWall() {
	glBindTexture(GL_TEXTURE_2D, textures[Wall]);
	glTranslatef(2.5, 2.5, 0.0);
	glPushMatrix();
	for (int i = 0; i < width; i++) {
		glPushMatrix();
		for (int j = 0; j < height; j++) {
			if (labyrint[i][j].value == '1') {
				drawBox(5, GL_QUADS);
			}
			if (labyrint[i][j].value == 'e') {
				displayExit();
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
	glBindTexture(GL_TEXTURE_2D, textures[Floor]);
	glPushMatrix();
	for (int i = 0; i < width; i++) {
		glPushMatrix();
		for (int j = 0; j < height; j++) {
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex2f(0.0, 0.0);
			glTexCoord2f(1.0, 0.0);
			glVertex2f(5., 0.0);
			glTexCoord2f(1.0, 1.0);
			glVertex2f(5., 5.);
			glTexCoord2f(0.0, 1.0);
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
	glBindTexture(GL_TEXTURE_2D, textures[Roof]);
	//glColor3f(1.0, 0.28, 0.28);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2.5);
	for (int i = 0; i < width; i++) {

		glPushMatrix();
		for (int j = 0; j < height; j++) {

			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex2f(0.0, 0.0);
			glTexCoord2f(1.0, 0.0);
			glVertex2f(5., 0.0);
			glTexCoord2f(1.0, 1.0);
			glVertex2f(5., 5.);
			glTexCoord2f(0.0, 1.0);
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

