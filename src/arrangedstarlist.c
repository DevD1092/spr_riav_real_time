#include <stdio.h>
#include <stdlib.h>
#include "arrangedstarlist.h"

starxy* createstarxy(int x, int y)
{
	starxy *i = malloc(sizeof(starxy));
	i -> x = x;
        i -> y = y;

        i -> nextxy = NULL;
        return i;
}

void releasestarxy(starxy *head, starxy *centre)
{
	starxy *i = head;
        starxy *nextxy = NULL;
        for(; i; i = nextxy) {
                nextxy = i -> nextxy;
                free(i);
        }
        free(centre);
}
