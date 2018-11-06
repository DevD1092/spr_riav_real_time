#include <stdlib.h>
#include "star.h"
#include "indvectpatt.h"
#include "info.h"

indvectpatt *getindvectpatt(star *stars_list, star *centre, info *headdist, int num)
{
        star *arrangehead = NULL;
        star *ref = stars_list;
        indvectpatt *next = NULL;
        indvectpatt *head = NULL;
        indvectpatt *current = NULL;
        int centre_x = centre -> x; // X-coord of the center star
        int centre_y = centre -> y; // Y coord of the center star
        int vector_x;
        int vector_y;
        float norm_vect_x;
        float norm_vect_y;
        float dist;
        int j;

        while(headdist){
                arrangehead = ref;
                while(arrangehead){
                    vector_x = arrangehead -> x - centre_x;
                    vector_y = arrangehead -> y - centre_y;
                    dist = (float)sqrt(vector_x * vector_x + vector_y * vector_y) / 1; //a scaling factor when doing the demo.
                    norm_vect_x = vector_x / dist;
                    norm_vect_y = vector_y / dist;
                    if(dist == headdist -> distance){
                        //append the star x,y to the arranged star list
                        next = createvector(vector_x, vector_y, norm_vect_x, norm_vect_y);
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
                        break;
                    }
                    arrangehead = arrangehead -> next;
                }
                headdist = headdist -> next;
        }

return head;
}

