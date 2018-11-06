#include <stdio.h>
#include <stdlib.h>
#include "indvectpatt.h"

indvectpatt* createvector(int x, int y, float norm_x, float norm_y)
{
	indvectpatt *i = malloc(sizeof(indvectpatt));
        i -> x = x;
        i -> y = y;
        i -> norm_x = norm_x;
        i -> norm_y = norm_y;
        i -> next = NULL;
        return i;
}

void releasevector(indvectpatt *head, indvectpatt *centre)
{
        indvectpatt *i = head;
        indvectpatt *next = NULL;
        for(; i; i = next) {
                next = i -> next;
                free(i);
        }
        free(centre);
}

