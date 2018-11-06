#include <stdio.h>
#include <stdlib.h>
#include "finalvectpatt.h"

finalvectpatt* createfinalvector(int x, int y)
{
	finalvectpatt *i = malloc(sizeof(finalvectpatt));
        i -> x = x;
        i -> y = y;
        i -> nextfinvect = NULL;
        return i;
}

void releasefinalvector(finalvectpatt *headfinvect, finalvectpatt *centrefinvect)
{
        finalvectpatt *i = headfinvect;
        finalvectpatt *nextfinvect = NULL;
        for(; i; i = nextfinvect) {
                nextfinvect = i -> nextfinvect;
                free(i);
        }
        free(centrefinvect);
}



