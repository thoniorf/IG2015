/*
 * LabReader.c
 *
 *  Created on: Jun 20, 2015
 *      Author: Antonio
 *
 */
#include "LabReader.h"
#include "pavimento.h"

bool freadlab() {
	FILE *ptr_file;
	char buf[width*height];

	ptr_file = fopen(maze, "r");
	if (ptr_file == NULL)
		return false;
	int i = 0;
	while (fgets(buf, width*height, ptr_file) != NULL)
	{
		initWall(i,buf);
		i++;
	}


	fclose(ptr_file);
	return true;
}
