#ifndef FINAL_VECT_PATT_H
#define FINAL_VECT_PATT_H

typedef struct finalvectordetail {
	int x;
	int y;
	struct finalvectordetail *nextfinvect;
} finalvectpatt;

extern finalvectpatt* createfinalvector(int x, int y);

extern void releasefinalvector(finalvectpatt *headfinvect, finalvectpatt *centrefinvect);

#endif



