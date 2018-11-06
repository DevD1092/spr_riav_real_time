#include "info.h"


void swap(info *a, info *b)
{
    float temp;
    temp = a->distance;
    a->distance = b->distance;
    b->distance = temp;
}
