#include <stdio.h>
#include "mpi.h"

long long fac(int n){
    if (n<0) return 0;
    long long res = 1;
    for(int i=2; i<=n; i++){
        res *= i;
    }
    return res;
}

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int num = rank+1;
    long long fac = fac(num);
    
    long long sv = fac;
    long long rv;
    
    MPI_Scan(&sv, &rv, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);
    
    printf("Process %d: Calculating factorial for number %d = %lld. Cummulative sum uptil now = %lld\n", rank, num, fac, rv);
    
    if(rank = size - 1){
        printf("Final factorial sum = %lld\n", rv);
    }
    MPI_Finalize();
}
