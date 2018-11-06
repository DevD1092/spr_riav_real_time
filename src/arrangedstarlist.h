#ifndef ARRANGED_STAR_LIST_H
#define ARRANGED_STAR_LIST_H

typedef struct arrangedstarlist {
	int x;
	int y;
	struct arrangedstarlist *nextxy;
} starxy;

extern starxy* createstarxy(int x, int y);

extern void releasestarxy(starxy *head, starxy *centre);

#endif

