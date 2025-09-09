#include <stdio.h>
#include "mpi.h"

long long factorial(int n){
    long long fact = 1;
    for(int i=2; i<=n; i++){
        fact *= i;
    }
    return fact;
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = size;
    long long my_fact = factorial(rank+1);
    long long prefix_sum = 0;

    MPI_Scan(&my_fact, &prefix_sum, 1, MPI_LONG_LONG_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Process %d: factorial(%d) = %lld, prefix sum = %lld\n", rank, rank+1, my_fact, prefix_sum);

    if(rank == size-1){
        printf("Total sum: %lld\n", prefix_sum);
    }
    
    MPI_Finalize();
    return 0;
}