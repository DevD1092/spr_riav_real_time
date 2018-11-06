#include <stdlib.h>
#include "star.h"
#include "arrangedstarlist.h"
#include "info.h"

starxy *arrangestarlist(star *stars_list, star *centre, info *headdist, int num)
{
        star *arrangehead = NULL;
        star *ref = stars_list;
        starxy *nextxy = NULL;
        starxy *headxy = NULL;
        starxy *currentxy = NULL;
        int centre_x = centre -> x; // X-coord of the center star
        int centre_y = centre -> y; // Y coord of the center star
        int vector_x;
        int vector_y;
        float dist;
        int j;

        while(headdist){
                arrangehead = ref;
                while(arrangehead){
                    vector_x = arrangehead -> x - centre_x;
                    vector_y = arrangehead -> y - centre_y;
                    dist = (float)sqrt(vector_x * vector_x + vector_y * vector_y) / 1; //a scaling factor when doing the demo.
                    if(dist == headdist -> distance){
                        //append the star x,y to the arranged star list
                        nextxy = createstarxy(arrangehead -> x, arrangehead -> y);
                        if(!headxy) {
                            headxy = nextxy;
                        }
                        if(!currentxy) {
                            currentxy = headxy;
                        }
                        else{
                            currentxy -> nextxy = nextxy;
                            currentxy = currentxy -> nextxy;
                        }
                        break;
                    }
                    arrangehead = arrangehead -> next;
                }
                headdist = headdist -> next;
        }

return headxy;
}
