#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int x = 0;

    if(rank == 0){
        x++;
        printf("Process %d sending %d...\n", rank, x);
        MPI_Ssend(&x, 1, MPI_INT, rank+1, rank, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, size-1, size-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Final value of x: %d.\n", x);
    } else if (rank == size - 1){
        MPI_Recv(&x, 1, MPI_INT, rank-1, rank-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received %d.\n", rank, x);
        x++;
        printf("Process %d sending %d...\n", rank, x);
        MPI_Send(&x, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&x, 1, MPI_INT, rank-1, rank-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received %d.\n", rank, x);
        x++;
        printf("Process %d sending %d...\n", rank, x);
        MPI_Ssend(&x, 1, MPI_INT, rank+1, rank, MPI_COMM_WORLD);
    }

    
    MPI_Finalize();
    return 0;
}