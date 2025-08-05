#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int countBits(int n){
    int count = 0;
    while(n>0){
        n >>= 1;
        count++;
    }
    return count;
}

int getComplement(int n){
    int sigBits = countBits(n);
    int mask = (1U << sigBits) - 1;
    return (~n) & mask;
}

int main(int argc, char *argv[]) {
    int r, c, i, j;
    scanf("%d %d", &r, &c);
    int **arr = malloc(r*sizeof(int *));
    for(i=0; i<r; i++){
        arr[i] = malloc(c*sizeof(int));
    }
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            scanf("%d", &arr[i][j]);
        }
    }
    #pragma omp parallel for collapse(2) schedule(dynamic)
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(i==r-1 || j==c-1)
        }
    }
}