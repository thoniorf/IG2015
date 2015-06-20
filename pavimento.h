/*
 * pavimento.h
 *
 *  Created on: Jun 19, 2015
 *      Author: thoniorf
 */

#ifndef PAVIMENTO_H_
#define PAVIMENTO_H_

#define width 25
#define height 25

struct Cords
{
	float x ;
	float y ;
	char value;
}labyrint[width][height];

void initWall(int i, char buf[width+1]);
void displayWall();
void displayFloor();
void displayRoof();

#endif /* PAVIMENTO_H_ */
