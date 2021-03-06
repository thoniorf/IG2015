/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *  Author: Chiara
 *
 */

#include "pavimento.h"

void initWall(int i, char buf[width + 1]) {
	for (int j = 0; j < width; j++) {
		labyrint[i][j].value = buf[j];
	}

}
void initFloor() {
	ai = -1;
	aj = -1;
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
bool vittoria_sfera(double x, double y) {
	if ((labyrint[(int) y][(int) x].value) == 'e') {
		stato = 1;
				printf("You Win");
				glutIdleFunc(NULL);
				glutPostRedisplay();
				exit(0);
		return true;
	}

	return false;
}

void displayExit() {
	glColor4f(1.,1.,1.,1.);
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
	glBindTexture(GL_TEXTURE_2D, textures[Win]);
	glutSolidSphere(raggio, 8.0, 8.0);
	glPopMatrix();

}

void displayWall() {
	glColor4f(1.,1.,1.,1.);
	glTranslatef(2.5, 2.5, 0.0);
	glPushMatrix();
	for (int i = 0; i < width; i++) {
		glPushMatrix();
		for (int j = 0; j < height; j++) {
			if (labyrint[i][j].value == '1') {
				glBindTexture(GL_TEXTURE_2D, textures[Wall]);
				drawBox(5, GL_QUADS);
			}
			if (labyrint[i][j].value == 'e') {
				//glBindTexture(GL_TEXTURE_2D, textures[Gate]);
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
	glColor4f(1.,1.,1.,1.);
	glBindTexture(GL_TEXTURE_2D, textures[Floor]);
	glPushMatrix();
	for (int i = 0; i < width; i++) {
		glPushMatrix();
		for (int j = 0; j < height; j++) {
			if((i == ai && j == aj) || (i == ai+1 && j == aj )|| (i == ai+1 && j == aj+1) ||( i == ai && j == aj+1) ){
				glColor4f(1.0,0.0,0.0,1.0);
			} else {
				glColor4f(1.,1.,1.,1.);
			}

			glBegin(GL_QUADS);
			glNormal3f(0.0,0.0,1.0);
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
	glColor4f(1.,1.,1.,1.);
	glBindTexture(GL_TEXTURE_2D, textures[Roof]);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2.5);
	for (int i = 0; i < width; i++) {
		glPushMatrix();
		for (int j = 0; j < height; j++) {
			glBegin(GL_QUADS);
			glNormal3f(0.0,0.0,-1.0);
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

