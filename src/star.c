#include <stdio.h>
#include <stdlib.h>
#include "star.h"

star* createStar(int x, int y, int magnitude)
{
	star *i = malloc(sizeof(star));
	i -> x = x;
        i -> y = y;
        i -> magnitude = magnitude;
        i -> next = NULL;
        return i;
}

void releaseStars(star *head, star *centre)
{
	star *i = head;
        star *next = NULL;
        for(; i; i = next) {
                next = i -> next;
                free(i);
        }
        free(centre);
}
