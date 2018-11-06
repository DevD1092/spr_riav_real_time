#include <stdio.h>
#include <math.h>
#include <star.h>
#include "info.h"
#include "sortdist.h"

info *getdistlist(star *stars_list, star *centre, int num, int fov)
{       info *head = NULL;
        info *i = NULL;
        info *next = NULL;
        info *current = NULL;
        star *ref = stars_list;
        //head = ref;
        int centre_x = centre -> x; // X-coord of the center star
        int centre_y = centre -> y; // Y coord of the center star
        int vector_x;
        int vector_y;
        float dist;
        info list[num]; // list which stores the distances
        //int i = 0;
        int j;
        while(ref) {
                vector_x = ref -> x - centre_x;
                vector_y = ref -> y - centre_y;
                dist = (float)sqrt(vector_x * vector_x + vector_y * vector_y) / 1; //a scaling factor when doing the demo.
                if(dist < fov){
                        next = createinfo(dist);
                        if(!head) {
                            head = next;
                        }
                        if(!current) {
                            current = head;
                        }
                        else{
                            current -> next = next;
                            current = current -> next;
                        }
                }
                ref = ref -> next;
        }
        i = head;

        // Arranging the distance list in ascending order.
        info *start = head;
        info *traverse;
        info *min;

        while(start->next){
            min = start;
            traverse = start->next;

            while(traverse){
			/* Find minimum element from array */
			if( min->distance > traverse->distance )
			{
				min = traverse;
			}
			traverse = traverse->next;
		}
		swap(start,min);			// Put minimum element on starting location
		start = start->next;
	}

        return head;
}


