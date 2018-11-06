#ifndef BOUND_VECT_PATT_H
#define BOUND_VECT_PATT_H

typedef struct boundvectordetail {
	int x;
	int y;
	struct boundvectordetail *nextbd;
} boundvectpatt;

extern boundvectpatt* createbdvector(int x, int y);

extern void releasebdvector(boundvectpatt *headbd, boundvectpatt *centrebd);

#endif


