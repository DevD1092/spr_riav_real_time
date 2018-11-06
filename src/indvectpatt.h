#ifndef IND_VECT_PATT_H
#define IND_VECT_PATT_H

typedef struct indvectordetail {
	int x;
	int y;
	float norm_x;
	float norm_y;
	struct indvectordetail *next;
} indvectpatt;

extern indvectpatt* createvector(int x, int y, float norm_x, float norm_y);

extern void releasevector(indvectpatt *head, indvectpatt *centre);

#endif

