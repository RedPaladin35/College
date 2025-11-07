#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int tc=0, lc=0;
    int trg;
    int arr[3][3];
    int temp[3];
    
    if(rank == 0){
        for(int i=0; i<3; i++){
            arr[0][i] = i+1;
            arr[1][i] = i+1;
            arr[2][i] = i+1;
        }
        scanf("%d", &trg);
    }
    
    MPI_Scatter((int*)arr, 3, MPI_INT, temp, 3, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&trg, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    for(int i=0; i<3; i++){
        if(trg == temp[i]){
            lc++;
        }
    }
    
    MPI_Reduce(&lc, &tc, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
        printf("%d\n", tc);
    }
}
