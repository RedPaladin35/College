#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank % 2 != 0){
        printf("Process Rank %d: World\n", rank);
    } else {
        printf("Process Rank %d: Hello\n", rank);
    }
    
    MPI_Finalize();
    return 0;
}