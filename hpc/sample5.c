#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int m = 4;
    int n = 4;
    
    int inp[m][n] = {
        {1, 2, 3, 4}, 
        {1, 2, 3, 1}, 
        {1, 1, 1, 1},
        {2, 1, 2, 1}
    };
    
    int li[m];
    int lo[m];
    
    MPI_Scatter((int*)inp, m, MPI_INT, li, 4, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scan(li, lo, m, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    
    int fo[m][n];
    
    MPI_Gather(lo, m, MPI_INT, (int*)fo, m, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Finalize();
}
