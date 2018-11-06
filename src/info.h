#ifndef INFO_H
#define INFO_H

typedef struct infodetail{
        float distance;
        struct infodetail *next;
} info;

extern info* createinfo(float distance);

extern void releaseinfo(info *head, info *centre);

#endif
