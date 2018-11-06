#include <stdio.h>
#include <math.h>
#include "boundvectpatt.h"
#include "finalvectpatt.h"
#include "indvectpatt.h"


finalvectpatt *getvectpatt(boundvectpatt *headbd, indvectpatt *headind, int num){

    boundvectpatt *ref = NULL;
    indvectpatt *ref1 = NULL;
    indvectpatt *ref2 = NULL;
    boundvectpatt *ref3 = NULL;
    ref = headbd;
    ref1 = headind;
    finalvectpatt *nextfinvect = NULL;
    finalvectpatt *headfinvect = NULL;
    finalvectpatt *currentfinvect = NULL;
    int add_vect_x;
    int add_vect_y;
    int final_vect_x;
    int final_vect_y;
    int i;
    int j;
    int l;
    int num1;
    int num2;
    int count;
    int sfov = num;

    // Four different added vector patterns have to be formed - starting with the four nearest points respectively
    for (i = 0; i < 4; i++){
        j = i;
        num = sfov;
        headbd = ref;
        headind = ref1;
        while(j!=0){
            headbd = headbd -> nextbd;
            headind = headind -> next;
            j--;
        }
        num1 = num-i-1;
        num2 = num-i-1;
        count = 0;
        while((num-i-1)!= 0){
            ref2 = headind;
            ref3 = headbd;
            num1 = num2-count;
            add_vect_x = 0;
            add_vect_y = 0;
            for(l=0 ; l<= num2-num1 ; num1++){
                add_vect_x = add_vect_x + ref3 -> x;
                add_vect_y = add_vect_y + ref3 -> y;
                ref2 = ref2 -> next;
                ref3 = ref3 -> nextbd;
            }

            final_vect_x = (add_vect_x * headind -> norm_x) + (add_vect_y * headind -> norm_y);
            final_vect_y = (add_vect_x * ref2 -> norm_x) + (add_vect_y * ref2 -> norm_y);

            nextfinvect = createfinalvector(final_vect_x, final_vect_y);
                        if(!headfinvect) {
                            headfinvect = nextfinvect;
                        }
                        if(!currentfinvect) {
                            currentfinvect = headfinvect;
                        }
                        else{
                            currentfinvect -> nextfinvect = nextfinvect;
                            currentfinvect = currentfinvect -> nextfinvect;
                        }
            num--;
            count = count + 1;
        }
    }

return headfinvect;

}

