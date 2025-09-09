#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int m;
    if(rank == 0){
        printf("Enter m: ");
        fflush(stdout);
        scanf("%d", &m);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int arr[size-1][m]; 
    int temp[m];        

    if(rank == 0){
        printf("Enter all elements for %d processes:\n", size-1);
        fflush(stdout);
        for(int i=0; i<size-1; i++){
            for(int j=0; j<m; j++){
                scanf("%d", &arr[i][j]);
            }
        }
    }

    if(rank == 0){
        for(int i=1; i<size; i++){
            MPI_Send(arr[i-1], m, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        int tot = 0, avg;
        for(int i=1; i<size; i++){
            MPI_Recv(&avg, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            tot += avg;
        }
        avg = tot / (size - 1);
        printf("Total average = %d\n", avg);
    } else {
        MPI_Recv(temp, m, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int tot = 0;
        for(int i=0; i<m; i++){
            tot += temp[i];
        }
        int avg = tot / m;
        MPI_Send(&avg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
