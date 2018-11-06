#include <stdio.h>
#include <stdlib.h>
#include "pair.h"

pair* createPair(int vect_x, int vect_y)
{
        pair *i = malloc(sizeof(pair));
        i -> vect_x = vect_x;
        i -> vect_y = vect_y;
        i -> next = NULL;
        return i;
}

void releasePairs(pair *head)
{
        pair *i = head;
        pair *next = NULL;
        for(; i; i = next) {
                next = i -> next;
                free(i);
        }
}


