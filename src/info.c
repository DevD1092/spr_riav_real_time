#include <stdio.h>
#include <stdlib.h>
#include "info.h"

info* createinfo(float distance)
{
	info *i = malloc(sizeof(info));
        i -> distance = distance;
        i -> next = NULL;
        return i;
}

void releaseinfo(info *head, info *centre)
{
	info *i = head;
        info *next = NULL;
        for(; i; i = next) {
                next = i -> next;
                free(i);
        }
        free(centre);
}
