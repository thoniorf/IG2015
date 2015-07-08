#include "nemici.h"

static GLdouble pi = 3.14159;

void iniz() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (i == 4 && j == 4)
				matrix[i][j] = 1;
			else if (i == 10 && j == 10)
				matrix[i][j] = 2;
			else if (i == 16 && j == 16)
				matrix[i][j] = 3;
			else if (i == 24 && j == 22)
				matrix[i][j] = 3;
			else
				matrix[i][j] = 0;
		}
	}
}

GLdouble xavanti() {
	return enemy.posx = enemy.posx + enemy.speed * cos((enemy.angle * pi) / 180);
}

GLdouble yavanti() {
	return enemy.posy = enemy.posy + enemy.speed * sin((enemy.angle * pi) / 180);
}

GLdouble xindietro() {
	return enemy.posx = enemy.posx
			- (enemy.speed - 0.1) * cos((enemy.angle * pi) / 180);
}

GLdouble yindietro() {
	return enemy.posy = enemy.posy
			- (enemy.speed - 0.1) * sin((enemy.angle * pi) / 180);
}

