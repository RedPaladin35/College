#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a, b;
    a=8;
    b=2;

    if(rank == 0){
        printf("Rank %d: %d + %d = %d\n", rank, a, b, a+b);
    } else if(rank == 1){
        printf("Rank %d: %d - %d = %d\n", rank, a, b, a-b);
    } else if(rank == 2){
        printf("Rank %d: %d x %d = %d\n", rank, a, b, a*b);
    } else if(rank == 3){
        printf("Rank %d: %d / %d = %d\n", rank, a, b, (b!=0)?(a/b):-1);
    }
    
    MPI_Finalize();
    return 0;
}