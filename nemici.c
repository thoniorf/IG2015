#include "nemici.h"
static GLdouble pi = 3.14159;
void iniz() {
	for(int i = 0; i < 5 ; i++){
		enemy[i].alive = 1;
		enemy[i].angle = 0;
		enemy[i].speed = 0.1;
		enemy[i].step = 100;
		enemy[i].currentstep = 0;
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (i == 4 && j == 4) {
				setEnemyCords(labyrint[i][j].x, labyrint[i][j].y, 0);

				enemies[i][j] = 0;
			} else if (i == 10 && j == 10) {
				setEnemyCords(labyrint[i][j].x, labyrint[i][j].y, 1);
				enemy[1].currentstep = 0;
				enemies[i][j] = 1;
			} else if (i == 16 && j == 16) {
				setEnemyCords(labyrint[i][j].x, labyrint[i][j].y, 2);
				enemies[i][j] = 2;
			} else if (i == 24 && j == 22) {
				setEnemyCords(labyrint[i][j].x, labyrint[i][j].y, 3);
				enemies[i][j] = 3;
			}

			else
				enemies[i][j] = -1;
		}
	}
}

void setEnemyCords(GLdouble x, GLdouble y, int i) {
	enemy[i].posx = x;
	enemy[i].posy = y;
}

void displayEnemy() {
	for (int i = 0; i < 5; i++) {
		if (enemy[i].alive == 1) {
			glPushMatrix();
			//glRotatef(enemy[i].angle, 0.0, 0.0, 1.0);
			glTranslatef(enemy[i].posx, enemy[i].posy, 1);
			drawBox(2, GL_QUADS);
			glPopMatrix();
		}
	}
}

void movement() {
	for (int i = 0; i < 5; i++) {
		if (enemy[i].alive == 1) {
			if(enemy[i].currentstep <= enemy[i].step){
				enemies[(int)(enemy[i].posy/5)][(int)(enemy[i].posx/5)] = -1;
				enemy[i].posx = enemy[i].posx + enemy[i].speed * cos((enemy[i].angle * pi) / 180);
				enemy[i].posy = enemy[i].posy + enemy[i].speed * sin((enemy[i].angle * pi) / 180);
				enemies[(int)(enemy[i].posy/5)][(int)(enemy[i].posx/5)] = i;
				enemy[i].currentstep += 1;
			} else {
				enemy[i].currentstep = 0;
				enemy[i].angle += 90;
			}

		}
	}
}


