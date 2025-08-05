#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int i, j;
    int **a = malloc(5*sizeof(int *));
    int **b = malloc(5*sizeof(int *));
    for(i=0; i<5; i++){
        a[i] = malloc(5*sizeof(int));
        b[i] = malloc(5*sizeof(int));
    }    
    int *min = malloc(5*sizeof(int));
    int *max = malloc(5*sizeof(int));
    
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            scanf("%d", &a[i][j]);
        }
    }

    #pragma omp parallel for private(j) num_threads(5)
    for(i=0; i<5; i++){
        min[i] = a[i][0];
        max[i] = a[i][0];
        for(j=1; j<5; j++){
            if(a[i][j]<min[i]) min[i] = a[i][j];
            if(a[i][j]>max[i]) max[i] = a[i][j];
        }
    }

    #pragma omp parallel for collapse(2)
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if(i == j){
                b[i][j] = 0;
            } else if(i > j){
                b[i][j] = max[i];
            } else {
                b[i][j] = min[i];
            }
        }
    }

    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            printf("%d\t", b[i][j]);
        }
        printf("\n");
    }
    for(i=0; i<5; i++){
        free(a[i]);
        free(b[i]);
    }
    free(a);
    free(b);
    free(min);
    free(max);
    return 0;
}