/*
 * ObjLoader.c
 *
 *  Created on: Jul 7, 2015
 *      Author: thoniorf
 */

#include "ObjLoader.h"

void initObj() {
	if (!readN('v', 0, &N_vertex))
		printf("Error could not found any vertex \n");
	if (!readN('t', 1, &N_tx))
		printf("Error could not found any tx vertex \n");
	if (!readN('n', 1, &N_normal))
		printf("Error could not found any normals \n");
	if (!readN('f', 0, &N_faces))
		printf("Error could not found any face \n");
	vertex = malloc(N_vertex * sizeof(GLTVector3));
	tx = malloc(N_tx * sizeof(GLTVector3));
	normal = malloc(N_normal * sizeof(GLTVector3));
	faces = malloc(N_faces * sizeof(struct face));
	//loadObj();
}

bool readN(char c, int pos, int *N_c) {

	FILE *ptr_file;
	char buf[256];

	ptr_file = fopen(ghost, "r");
	if (ptr_file == NULL)
	{
		printf("File doesn't exist or wrong path\n");
		return false;
	}
	*N_c = 0;
	while (fgets(buf, 256, ptr_file) != NULL) {
		if (buf[pos] == c)
		{
			*N_c+=1;
		}

	}
	fclose(ptr_file);
	return true;
}
bool loadObj() {
	int i_v = 0, i_vt = 0, i_vn = 0, i_f = 0;
	FILE *ptr_file;
	char buf[256];
	char *tmp;
	ptr_file = fopen(ghost, "r");
	if (ptr_file == NULL)
		return false;
	while (fgets(buf, 256 * 265, ptr_file) != NULL) {
		tmp = buf;
		switch (buf[0]) {
		case 'v':
			switch (buf[1]) {
			case 't':
				tmp = strtok(&buf[3]," ");
				tx[i_vt][0] = atof(tmp);
				tmp = strtok(NULL," ");
				tx[i_vt][1] = atof(tmp);
				i_vt ++;
				break;
			case 'n':
				tmp = strtok(&buf[3]," ");
				normal[i_vn][0] = atof(tmp);
				tmp = strtok(NULL," ");
				normal[i_vn][1] = atof(tmp);
				tmp = strtok(NULL," ");
				normal[i_vn][2] = atof(tmp);
				i_vn ++;
				break;
			default:
				tmp = strtok(&buf[2]," ");
				vertex[i_v][0] = atof(tmp);
				tmp = strtok(NULL," ");
				vertex[i_v][1] = atof(tmp);
				tmp = strtok(NULL," ");
				vertex[i_v][1] = atof(tmp);
				i_v ++;
				break;
			}
			break;
		case 'f':
			tmp = strtok(tmp,"/");
			faces[i_f].x1 =atoi(tmp);
			tmp = strtok(tmp,"/");
			faces[i_f].t1 =atoi(tmp);
			tmp = strtok(tmp,"/");
			faces[i_f].n1 =atoi(tmp);
			tmp = strtok(tmp,"/");
			faces[i_f].x2 =atoi(tmp);
			tmp = strtok(tmp,"/");
			faces[i_f].t2 =atoi(tmp);
			tmp = strtok(tmp,"/");
			faces[i_f].n2 =atoi(tmp);
			tmp = strtok(tmp,"/");
			faces[i_f].x3 =atoi(tmp);
			tmp = strtok(tmp,"/");
			faces[i_f].t3 =atoi(tmp);
			tmp = strtok(tmp,"/");
			faces[i_f].n3 =atoi(tmp);
			i_f++;
			break;
		default:
			break;
		}
	}
	fclose(ptr_file);
	return true;
}
void loadTexture(){

}
void displayObj(GLfloat scale ) {
	glBufferData(GL_ARRAY_BUFFER, N_vertex* sizeof(GLTVector3), &vertex[0], GL_STATIC_DRAW);
	glPushMatrix();
	//glScalef(-scale,-scale,-scale);
	glBegin(GL_POLYGON);
	for(int i = 0; i < N_faces; i++){
		// X1
		glNormal3fv(&normal[faces[i].n1-1][0]);
		glTexCoord2fv(&tx[faces[i].t1-1][0]);
		glVertex3fv(&vertex[faces[i].x1-1][0]);
		// X2
		glNormal3fv(&normal[faces[i].n2-1][0]);
		glTexCoord2fv(&tx[faces[i].t2-1][0]);
		glVertex3fv(&vertex[faces[i].x2-1][0]);
		// X3
		glNormal3fv(&normal[faces[i].n3-1][0]);
		glTexCoord2fv(&tx[faces[i].t3-1][0]);
		glVertex3fv(&vertex[faces[i].x3-1][0]);
	}
	glEnd();
	glPopMatrix();
}

void freeObj()
{
	free(vertex);
	free(normal);
	free(tx);
	free(faces);
}
