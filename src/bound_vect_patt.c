#include <stdio.h>
#include <math.h>
#include "indvectpatt.h"
#include "boundvectpatt.h"


boundvectpatt *getboundvectpatt(indvectpatt *head, int num){

    indvectpatt *ref = NULL;
    ref = head;
    boundvectpatt *nextbd = NULL;
    boundvectpatt *headbd = NULL;
    boundvectpatt *currentbd = NULL;
    int vector_bound_x;
    int vector_bound_y;
    int i;
    int j;
    int sfov = num;
    float dist;

    // Four different added vector patterns have to be formed - starting with the four nearest points respectively
    for (i = 0; i < 4; i++){
        j = i;
        num = sfov;
        head = ref;
        while(j!=0){
            head = head -> next;
            j--;
        }
        while((num-i-1)!= 0){
            vector_bound_x = head -> next -> x - head -> x;
            vector_bound_y = head -> next -> y - head -> y;
            nextbd = createbdvector(vector_bound_x, vector_bound_y);
                        if(!headbd) {
                            headbd = nextbd;
                        }
                        if(!currentbd) {
                            currentbd = headbd;
                        }
                        else{
                            currentbd -> nextbd = nextbd;
                            currentbd = currentbd -> nextbd;
                        }
            head = head -> next;
            num--;
        }
    }

return headbd;

}
