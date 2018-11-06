#include <stdlib.h>
#include "findCentre.h"

star* findCentreStar(star **head, int x, int y)
{
        star *centre = *head;
        star *next = centre -> next;
        star *temp1 = NULL;
        star *temp2 = NULL;
        int d_next_square;
        int d_square = (centre -> x - x) * (centre -> x - x) + (centre -> y - y) * (centre -> y - y);

        while(next) {
                d_next_square = (next -> x - x) * (next -> x - x) + (next -> y - y) * (next -> y - y);
                if(d_square > d_next_square) {
                        d_square = d_next_square;
                        centre = next;
                        next = centre -> next;
                }
                else {
                        next = next -> next;
                }
        }

        //delete the centre_star from the stars_list
        if(centre == *head) {
                *head = (*head) -> next;
                centre -> next = NULL;
                return centre;
        }
        else if(!centre -> next) {
                temp1 = *head;
                while(temp1 -> next != centre) {
                        temp1 = temp1 -> next;
                }
                temp1 -> next = NULL;
                return centre;
        }
        else {
                temp1 = malloc(sizeof(star));
                temp1 -> x = centre -> x;
                temp1 -> y = centre -> y;
                temp1 -> magnitude = centre -> magnitude;
                temp1 -> next = NULL;
                temp2 = centre -> next;
                centre -> x = temp2 -> x;
                centre -> y = temp2 -> y;
                centre -> magnitude = temp2 -> magnitude;
                centre -> next = temp2 -> next;
                free(temp2);
                return temp1;
        }
}

