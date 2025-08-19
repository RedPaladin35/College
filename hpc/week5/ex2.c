#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n = 10;
    
    if(rank == 0){
        printf("Process %d sending %d to all threads...\n", rank, n);
        for(int i=1; i<size; i++){
            MPI_Ssend(&n, 1, MPI_INT, i, i, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&n, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received %d\n", rank, n);
    }
    
    MPI_Finalize();
    return 0;
}