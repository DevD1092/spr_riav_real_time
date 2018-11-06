#ifndef PAIR_H
#define PAIR_H

typedef struct vector_pair {
        int vect_x;
        int vect_y;
        struct vector_pair *next;
} pair;

extern pair* createPair(int vect_x, int vect_y);

extern void releasePairs(pair *head);

#endif

