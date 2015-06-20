/*
 * LabReader.c
 *
 *  Created on: Jun 20, 2015
 *      Author: thoniorf
 */
#include "LabReader.h"
#include "pavimento.h"
bool freadlab() {
	FILE *ptr_file;
	char buf[width + 1];

	ptr_file = fopen("./labs/uno.txt", "r");
	if (ptr_file == NULL)
		return false;
	int i = 0;
	while (fgets(buf, width+1, ptr_file) != NULL)
	{
		if(i < width)
			initWall(i,buf);
		else
			break;
		printf("%s", buf);
		i++;
	}


	fclose(ptr_file);
	return true;
}
