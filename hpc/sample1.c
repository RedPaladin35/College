#include<stdio.h>
#include"mpi.h"

int main(int argc, char *argv[]){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int m = 5;
    int n = 4;
    
    int te = m*n;
    int end_buffer[te];
    double recv_average[n];
    
    if(rank == 0){
        for(int i=0; i<te; i++){
            send_buffer[i] = i+1;
        }
    }
    
    int* recv_buffer = (int*)malloc(m*sizeof(int));
    MPI_Scatter(send_buffer, m, MPI_INT, recv_buffer, m, MPI_INT, 0, MPI_COMM_WORLD);
    int ls = 0;
    for(int i=0; i<m; i++){
        ls += recv_buffer[i];
    }
    double la = (double)ls/m;
    MPI_Gather(&la, 1, MPI_DOUBLE, recv_average, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
        int gs = 0;
        for(int i=0; i<n; i++){
            gs += recv_average[i];
        }
        double ga = (double)gs/n;
    }
}
