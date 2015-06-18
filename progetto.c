#include <windows.h>
#include <GL/glut.h>
#include <math.h>
//#include "pavimento.c"

static GLdouble pi = 3.14159;
static GLdouble angle = 0.0;
static GLdouble posx = 0.0;
static GLdouble posy = 0.0;
static GLdouble posfx = 1.0;
static GLdouble posfy = 0.0;

float zRot = 0.0;
float xGo = 0.0;
struct Cordinate {
	double x, y, z;
} Co[3];

struct Muro
{
	int e;
} Muro[25][25];



void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
int i,j;
	for(i=0; i<25; i++)
	{
		for(j=0; j<25; j++)
			Muro[i][j].e=0;
	}



	for(i=0; i<25; i++)
	{
		Muro[0][i].e=1;
		Muro[24][i].e=1;
		Muro[i][0].e=1;
		Muro[i][24].e=1;

	}
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.1, 0.1, 1.0);

	//resetCoordinate();

	/*QUADRATO*/
	//gluLookAt(Co[0].x, Co[0].y, Co[0].z, Co[1].x+Co[0].x, Co[1].y+Co[0].y, Co[1].z+ Co[0].z, Co[2].x,
		//	Co[2].y, Co[2].z);
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	gluLookAt(posx, posy, 1.5, posx + posfx, posy + posfy, 1.5, 0.0, 0.0, 1.0);

	glPushMatrix();
	//ruota su se stesso
	//glRotatef(45, 0.0, 0.0, 1.0);
	//glTranslatef(-16.0, -16.0, 0.0);


	displayPav();
	 displayMura ();
	 displayObjs();
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 500.0);


}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		angle += 2.0;
		posfx = cos((angle*pi)/180);
		posfy = sin((angle*pi)/180);
		break;
	case 'd':
		angle -= 2.0;
		posfx = cos((angle*pi)/180);
		posfy = sin((angle*pi)/180);
		break;
	case 'w':
		posx = posx + cos((angle*pi)/180);
		posy = posy + sin((angle*pi)/180);
		break;
	case 's':
		posx = posx - cos((angle*pi)/180);
		posy = posy - sin((angle*pi)/180);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
	return 0;
}
