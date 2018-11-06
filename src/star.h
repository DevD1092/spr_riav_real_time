#ifndef STAR_H
#define STAR_H

typedef struct starDetail {
	int x;
	int y;
	int magnitude;
	struct starDetail *next;
} star;

extern star* createStar(int x, int y, int magnitude);

extern void releaseStars(star *head, star *centre);

#endif
