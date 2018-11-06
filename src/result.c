#include <stdio.h>
#include "result.h"
#include "finalvectpatt.h"
#include "info.h"
#include "spd.h"
#include "math.h"

#define DIST_TOL 8
#define VECT_TOL 12

void result(finalvectpatt *headfinvect, info *head, SPD spd[], int sfov, int spd_size) {

        info *ref = NULL;
        ref = head;
        finalvectpatt *ref1 = NULL;
        ref1 = headfinvect;
        int i; //ID index in the SPD
        int j; // ID of the distance in the image (max.4)
        int k;
        int l;
        int m; // ID in the SPD sequence
        int count; // Count the number of matches in the vector pattern
        int num; // Intermediate variable 0
        int num1; // Intermediate variable 1
        int max_vote = 0; // Maximum vote
        int starid = 0; // Reference star id for the maximum vote


        for (i=0 ; i<spd_size; i++){
            ref = head;
            ref1 = headfinvect;
            count = 0;
            for (j=0 ; j<3 ; j++){
                if(fabs(spd[i].stardist - ref -> distance) < DIST_TOL){
                    break; // CHANGE this to a list -> Need to get all the matches. Not only the initial first match of the distance.
                }
                else{
                    ref = ref -> next;
                }
            }
            if(j == 3){
                continue;
            }
//          printf("\nDistance matched: ID:%d      %d\n",i,spd[i].stardist);

            num = j*sfov - j*(j+1)/2;
            for (k=0 ; k<num ; k++){
                ref1 = ref1 -> nextfinvect;
            }
//          num1 = (j+1)*sfov - (j+1)*(j+2)/2;
//          for(l=k-1; l<num1 ; l++){
            num1 = sfov - (j+1);
            for(l=0; l<num1 ; l++){
                //code for matching
                for(m=0 ; m < spd[i].starCounts ; m++){

                    if(fabs(ref1 -> x - spd[i].start -> vect_x) < VECT_TOL){
                        if(fabs(ref1 -> y - spd[i].start -> vect_y) < VECT_TOL){
                            count = count + 1;
                            break;
                        }
                    }
                    spd[i].start = spd[i].start -> next;
                }
                ref1 = ref1 -> nextfinvect;
            }

            if(count > max_vote){
                max_vote = count;
                starid = i;
            }

            //printf("\nID: %d    Vote:%d\n",i,count);
        }

        printf("\nStar ID: %d       Maximum vote: %d\n",starid+1,max_vote);



        /*printf("The star ID is %d\n", spd[id].starId);
        printf("The RA is %f\n", spd[id].starRA);
        printf("The DEC is %f\n", spd[id].starDEC);
		printf("The Star ID is %04d, RA = %05.2f, DEC = %.2f------", spd[id].starId, spd[id].starRA, spd[id].starDEC);*/
}


