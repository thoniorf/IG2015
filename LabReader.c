/*
 * LabReader.c
 *
 *  Created on: Jun 20, 2015
 *      Author: Antonio
 *      Modifier: Antonio 20/giu/2015
 */
#include "LabReader.h"
#include "pavimento.h"

bool freadlab() {
	FILE *ptr_file;
	char buf[width*height];

	ptr_file = fopen("./labs/uno.txt", "r");
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
