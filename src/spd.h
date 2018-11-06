#ifndef SPD_H
#define SPD_H

#include "pair.h"

typedef struct {
        int starId;
        int starCounts;
        float starRA;
        float starDEC;
        int stardist;
        pair *start;
} SPD;

#endif

