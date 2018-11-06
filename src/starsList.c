#include <stdlib.h>
#include "starsList.h"

typedef struct {
        int sumOfXproduct;
        int sumOfYproduct;
        int sum;
        int area;
} sumOfProduct;

static void dfs(int m, int n, int M, int N, int level, sumOfProduct* data, unsigned char image[][N], unsigned char** ref);

star* getStarsList(int m, int n, int level, int threshold, int *starsNum, unsigned char image[][n])
{
        unsigned char **ref;
        int i;
        int j;
        int count = 0;
        star *next = NULL;
        star *head = NULL;
        star *current = NULL;
        sumOfProduct* data = malloc(sizeof(sumOfProduct));
        data -> sumOfXproduct = 0;
        data -> sumOfYproduct = 0;
        data -> sum = 0;
        data -> area = 0;

        ref = malloc(sizeof(unsigned char *) * m);
        for(i = 0; i < m; i++) {
                *(ref + i) = malloc(sizeof(unsigned char) * n);
        }

        for(i = 0; i < m; i++) {
                for(j = 0; j < n; j++) {
                        ref[i][j] = 0;
                }
        }

        for(i = 0; i < m; i++) {
                for(j = 0; j < n; j++) {
                        if(image[i][j] > level && !ref[i][j]) {
                                data -> sumOfXproduct = 0;
                                data -> sumOfYproduct = 0;
                                data -> sum = 0;
                                data -> area = 0;
                                dfs(i, j, m, n, level, data, image, ref);
				if(data -> area > threshold) {
                                	count++;
                                	next = createStar(data -> sumOfXproduct / data -> sum, data -> sumOfYproduct / data -> sum, data -> area);
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
                        }
                }
        }
        *starsNum = count;

	free(data);
        for(i = 0; i < m; i++) {
                free(ref[i]);
        }
        free(ref);
        return head;
}

void dfs(int m, int n, int M, int N, int level, sumOfProduct * data, unsigned char image[][N], unsigned char** ref)
{
        int i;
        int nm;
        int nn;
        char dm[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
        char dn[8] = {1, 1, 1, 0, -1, -1, -1, 0};
        ref[m][n] = 1;
        data -> sumOfXproduct = data -> sumOfXproduct + (int)image[m][n] * n;
        data -> sumOfYproduct = data -> sumOfYproduct + (int)image[m][n] * m;
        data -> sum = data -> sum + (int)image[m][n];
        data -> area = data -> area + 1;
        for(i = 0; i < 8; i++) {
                nm = m + dm[i];
                nn = n + dn[i];
                if(nm >= 0 && nm < M && nn >= 0 && nn < N && image[nm][nn] > level && !ref[nm][nn]) {
                        dfs(nm, nn, M, N, level, data, image, ref);
                }
        }
}


