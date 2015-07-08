#include "nemici.h"
static GLdouble pi = 3.14159;
void initEnemy() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			enemies[i][j] = -1;
		}
	}
	int li,lj;
	for(int i = 0; i < 6 ; i++){
		while(labyrint[li][lj].value == 'p' || enemies[li][lj] != -1 )
		li = rand()%23+1;
		lj = rand()%23+1;
		enemy[i].alive = 1;
		enemy[i].angle = 0;
		enemy[i].speed = 0.2;
		enemy[i].step = 200;
		enemy[i].currentstep = 0;
		setEnemyCords(labyrint[li][lj].x, labyrint[li][lj].y, i);
		enemies[li][lj] = i;
	}
}

void setEnemyCords(GLdouble x, GLdouble y, int i) {
	enemy[i].posx = x;
	enemy[i].posy = y;
}

void displayEnemy() {
	for (int i = 0; i < 6; i++) {
		if (enemy[i].alive == 1) {
			glPushMatrix();
			glTranslatef(enemy[i].posx, enemy[i].posy, 1);
			drawBox(2, GL_QUADS);
			glPopMatrix();
		}
	}
}

void movement() {
	for (int i = 0; i < 6; i++) {
		if (enemy[i].alive == 1) {
			if(enemy[i].currentstep <= enemy[i].step){
				enemies[(int)(enemy[i].posy/5)][(int)(enemy[i].posx/5)] = -1;
				enemy[i].posx = enemy[i].posx + enemy[i].speed * cos((enemy[i].angle * pi) / 180);
				enemy[i].posy = enemy[i].posy + enemy[i].speed * sin((enemy[i].angle * pi) / 180);
				enemies[(int)(enemy[i].posy/5 + enemy[i].speed * sin((enemy[i].angle * pi) / 180))][(int)(enemy[i].posx/5 + enemy[i].speed * cos((enemy[i].angle * pi) / 180))] = i;
				enemy[i].currentstep += 1;
			} else {
				enemy[i].currentstep = 0;
				enemy[i].angle += 90;
			}

		}else {
			enemies[(int)(enemy[i].posy/5)][(int)(enemy[i].posx/5)] = -1;
		}
	}
}


