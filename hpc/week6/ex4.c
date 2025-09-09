#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int r = 3, c = 3;
    int arr[r][c], elem;

    if(rank == 0){
        printf("Enter elements for 3 x 3 matrix:\n");
        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++){
                scanf("%d", &arr[i][j]);
            }
        }
        printf("Enter element to search: ");
        fflush(stdout);
        scanf("%d", &elem);
    }

    MPI_Bcast(&elem, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int row_lcl[c];
    MPI_Scatter(arr, c, MPI_INT, row_lcl, c, MPI_INT, 0, MPI_COMM_WORLD);

    int lc = 0;
    for(int i=0; i<c; i++){
        if(row_lcl[i] == elem){
            lc++;
        }
    }

    int total_count = 0;
    MPI_Reduce(&lc, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Number of occurences of %d in the matrix: %d\n", elem, total_count);
    }
    
    MPI_Finalize();
    return 0;
}