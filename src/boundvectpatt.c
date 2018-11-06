#include <stdio.h>
#include <stdlib.h>
#include "boundvectpatt.h"

boundvectpatt* createbdvector(int x, int y)
{
	boundvectpatt *i = malloc(sizeof(boundvectpatt));
        i -> x = x;
        i -> y = y;
        i -> nextbd = NULL;
        return i;
}

void releasebdvector(boundvectpatt *headbd, boundvectpatt *centrebd)
{
        boundvectpatt *i = headbd;
        boundvectpatt *nextbd = NULL;
        for(; i; i = nextbd) {
                nextbd = i -> nextbd;
                free(i);
        }
        free(centrebd);
}


