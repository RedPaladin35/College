#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int i, j, r, c;
    scanf("%d %d", &r, &c);
    double **mat = (double **)malloc(r*sizeof(double *));
    for(i=0; i<r; i++){
        mat[i] = (double *)malloc(c*sizeof(double));
    }
    double *vec = (double *)malloc(c*sizeof(double));
    double *res = (double *)malloc(r*sizeof(double));

    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            scanf("%lf", &mat[i][j]);
        }
    }
    for(i=0; i<c; i++){
        scanf("%lf", &vec[i]);
    }

    #pragma omp parallel for private(j) num_threads(5)
    for(i=0; i<r; i++){
        res[i] = 0;
        for(j=0; j<c; j++){
            res[i] += mat[i][j] * vec[j];
        }
    }
    for(i=0; i<r; i++){
        printf("%lf\n", res[i]);
    }
    printf("\n");
    for(i=0; i<r; i++){
        free(mat[i]);
    }
    free(mat);
    free(vec);
    free(res);
    return 0;
}