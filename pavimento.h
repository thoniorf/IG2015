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
	int value;
}labyrint[width][height];

void displayWall();
void displayFloor();
void displayRoof();

#endif /* PAVIMENTO_H_ */
