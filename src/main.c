#define AUTHORS Mehta Deval & Zhang Yexin

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "star.h"
#include "starsList.h"
#include "info.h"
#include "sortdist.h"
#include "findCentre.h"
#include "arrangedstarlist.h"
#include "indvectpatt.h"
#include "boundvectpatt.h"
#include "finalvectpatt.h"
#include "pair.h"
#include "spd.h"


#define HEIGHT 1024
#define WIDTH 1024
#define LEVEL 80
#define THRESHOLD 1
#define CENTRE_X 512
#define CENTRE_Y 512
#define FOV 510
#define DIST_TOL 8
#define VECT_TOL 12
#define SPD_SIZE_1 4956
#define SPD_SIZE_2 6903

//static SPD spd[SPD_SIZE_1];
static SPD spd[SPD_SIZE_2];

int main (void)
{
    star *head = NULL; // Head of the star list.
    star *centre = NULL; // Centre address of the star list.
    star *i = NULL;
    star *j = NULL;
    info *headdist = NULL; // Head of the sorted distance list.
    info *k = NULL;
    starxy *headxy = NULL; // Head of the arranged x,y star list.
    starxy *l = NULL;
    indvectpatt *headindvect = NULL; // Head of the arranged individual vector pattern
    indvectpatt *m = NULL;
    boundvectpatt *headbdvect = NULL; // Head of the boundary vector pattern
    boundvectpatt *n = NULL;
    finalvectpatt *headfinvect = NULL; // Head of the final vector pattern
    finalvectpatt *o = NULL;

    // Timing parameters
    clock_t begin1;
	clock_t end1;
	double time_spent_img_read; // Time for reading the image.
	clock_t begin2;
	clock_t end2;
	double time_spent_img_pro; // Time for pre-processing the image.
	clock_t begin3;
	clock_t end3;
	double time_spent_algo; // Run-time of the algorithm.
	double tot_time; // Total run-time of the full thing.


	int stars_num;
	unsigned char image[HEIGHT][WIDTH] = {0};
	unsigned char fileName[50];
	int container;
	int x;
	int y;
	int id = 0;
	int sfov = 0; // Number of stars in the FOV of the center star.


    /*used for loading SPD database*/
    pair *start = NULL;
	pair *current = NULL;
	pair *next = NULL;

	FILE *database = fopen("C:\\Users\\MEHT0004\\Desktop\\Vector\\vect_patt\\spd_vp_1.bin", "rb");
	union {
		char bytes[4];
		int integer;
		float floating;
	} convert;

    /*load the SPD database*/
	//for(x = 0; x < SPD_SIZE_1; x++) {
	for(x = 0; x < SPD_SIZE_2; x++) {
		fread(convert.bytes, 4, 1, database);
		spd[x].starId = convert.integer;
		fread(convert.bytes, 4, 1, database);
		spd[x].starCounts = convert.integer;
		fread(convert.bytes, 4, 1, database);
		spd[x].starRA = convert.floating;
		fread(convert.bytes, 4, 1, database);
		spd[x].starDEC = convert.floating;
		fread(convert.bytes, 4, 1, database);
		spd[x].stardist = convert.integer;
		spd[x].start = malloc(sizeof(pair));
		fread(convert.bytes, 4, 1, database);
		spd[x].start -> vect_x = convert.integer;
		fread(convert.bytes, 4, 1, database);
		spd[x].start -> vect_y = convert.integer;
		spd[x].start -> next = NULL;
		current = spd[x].start;
		for(y = 1; y < spd[x].starCounts; y++) {
			next = malloc(sizeof(pair));
			fread(convert.bytes, 4, 1, database);
			next -> vect_x = convert.integer;
			fread(convert.bytes, 4, 1, database);
			next -> vect_y = convert.integer;
			next -> next = NULL;
			current -> next = next;
			current = next;
		}
		current -> next = spd[x].start;
	}


	// Reading the image stars from here and subsequent algorithm steps start from here.
	FILE *fp = NULL;

    begin1 = clock();
    fp = fopen("C:\\Users\\MEHT0004\\Desktop\\Vector\\vect_patt\\hehe.txt", "r");
		for(x = 0; x < HEIGHT; x++) {
			for(y = 0; y < WIDTH; y++) {
				fscanf(fp, "%d", &container); //image.txt
				image[x][y] = container;
				//image[x][y] = fgetc(fp);  //test.txt
			}
		}
		fclose(fp);
    end1 = clock();

    begin2 = clock();
        // Get the stars in the image.
		head = getStarsList(HEIGHT, WIDTH, LEVEL, THRESHOLD, &stars_num, image);

        i = head;
		/*printf("%d stars found\n", stars_num);
			while(i) {
					printf("%d: x = %2d    y = %2d  area = %d\n", id, i -> x, i -> y, i -> magnitude);
					i = i -> next;
					id++;
			}*/
    end2 = clock();

    begin3 = clock();
        /*find out the centre star*/
		centre = findCentreStar(&head, CENTRE_X, CENTRE_Y);
		j = centre;
        stars_num--;
        //printf("\nCenter star information: x = %2d    y = %2d  area = %d\n", j -> x, j -> y, j -> magnitude);

        /* Star pattern recognition will start from here */
        // Getting distance list in ascending order.
        headdist = getdistlist(head,centre,stars_num,FOV);
        k = headdist;
        //printf("\nDistance list in ascending order is: \n");

        while(k){
            //printf("%f \n", k -> distance);
            k = k -> next;
            sfov++;
        }

        //printf("\nNumber of stars in the FOV of the center star: %d \n", sfov);

        if(sfov <= 4){
            printf("Not enough number of stars in the FOV of the center star!");
        }

        // Getting the corresponding star coords in the arranged distance list order.

        headxy = arrangestarlist(head,centre,headdist,sfov);
        l = headxy;
        /*while(l) {
                printf(" x = %2d    y = %2d  \n", l -> x, l -> y);
                l = l -> nextxy;
        }*/

        // Vector pattern generation function

        //1. Get the individual vector patterns first
        //printf("\nIndividual vector pattern \n");
        headindvect = getindvectpatt(head,centre,headdist,sfov);
        m = headindvect;
        /*while(m){
            printf("x = %d      y = %d      normx = %f      normy = %f\n", m -> x, m -> y, m -> norm_x, m -> norm_y);
            m = m -> next;
        }*/

        //2. Get the boundary vector pattern.
        //printf("\nBoundary vector pattern \n");
        headbdvect = getboundvectpatt(headindvect, sfov);
        n = headbdvect;
        /*while(n){
            printf("x = %d      y = %d \n", n -> x, n -> y);
            n = n -> nextbd;
        }*/

        //3. Generate the boundary vector pattern into new frame and their additive along the path too!
        headfinvect = getvectpatt(headbdvect,headindvect, sfov);
        //printf("\nFinal vector pattern \n");
        o = headfinvect;
        /*while(o){
            printf("x = %d      y = %d \n", o -> x, o -> y);
            o = o -> nextfinvect;
        }*/

        //4. Counting and voting of the number of matches in the SPD.
        result(headfinvect, headdist, spd, sfov, SPD_SIZE_2);
        releaseStars(head, centre);
		releasePairs(start);
        end3 = clock();
        time_spent_img_read = (double)(end1 - begin1) / CLOCKS_PER_SEC;
        time_spent_img_pro = (double) (end2 - begin2) / CLOCKS_PER_SEC;
        time_spent_algo = (double) (end3 - begin3) / CLOCKS_PER_SEC;
		printf("\nTime for image read = %.3fs!\n", time_spent_img_read);
		printf("\nTime for pre-processing the image = %.4fs!\n", time_spent_img_pro);
		printf("\nRun-time for the algorithm = %.3fs!\n", time_spent_algo);
		tot_time = time_spent_img_read + time_spent_img_pro + time_spent_algo;
		printf("\nTotal run-time = %.3fs!\n", tot_time);

        return 0;
}

