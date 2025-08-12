#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int x = 2;

    printf("Rank %d: %d to the power %d = %d\n", rank, x, rank, (int)pow(x, rank));
    MPI_Finalize();
}