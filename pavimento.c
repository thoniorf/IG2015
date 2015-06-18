/*
 * pavimento.c
 *
 *  Created on: 18/giu/2015
 *      Author: Chiara
 */

#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

/*unsigned int DimGrigliaX = 8; //dimensione della griglia x
unsigned int DimGrigliaY = 8; //dimensione della griglia y
unsigned int X = 4; //misura x
unsigned int Y = 4; //misura y
*/


struct Muro
{
	int e;
} Muro[25][25];

void displayObjs(){

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(45.0,25.0,0.0);
	glScalef(1.0,1.0,3.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, .25, 0.1);
	glTranslatef(25.,50.0,0.0);
	glutSolidSphere(3.0,10,5);
	glPopMatrix();

}

void displayMura ()
{

	int i,j;
	glPushMatrix();
	glTranslatef(2.5,2.5,0.0);
	for(i=0; i<25; i++)	{

		glPushMatrix();
		for(j=0; j<25; j++)
		{
			if(Muro[i][j].e==1){
				glColor3f(1.0f, 0.0f, 1.0f);
				glutSolidCube(5);
				glTranslatef(5.0,0.0,0.0);
			}
		}

		glPopMatrix();
		glTranslatef(0.0,5.0,0.0);

	}
}


void displayPav() {

	glColor3f(0.1, 0.1, 1);

	GLint n_quads = 25;
	int i,j;
	glPushMatrix();
	for ( i = 0; i < n_quads; i++)
	{

		glPushMatrix();
		for (j = 0; j < n_quads; j++)
		{

			glBegin(GL_QUADS);
			glVertex2f(0.0, 0.0);
			glVertex2f(5., 0.0);
			glVertex2f(5., 5.);
			glVertex2f(0.0, 5.);
			glEnd();
			glTranslatef(5., 0.0, 0.0);
		}
		glPopMatrix();
		glTranslatef(0.0,5.,0.0);
	}

	glPopMatrix();
		glFlush();
}

