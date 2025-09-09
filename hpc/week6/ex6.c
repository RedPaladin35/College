#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define ROWS 4
#define COLS 4

// Define custom MPI operation outside main
void vector_add_op(void *invec, void *inoutvec, int *len, MPI_Datatype *dtype) {
    int *in_vals = (int *)invec;
    int *inout_vals = (int *)inoutvec;
    for(int i = 0; i < *len; i++) {
        inout_vals[i] += in_vals[i];
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int matrix[ROWS][COLS];
    int local_row[COLS];
    int prefix_row[COLS];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != ROWS) {
        if(rank == 0) {
            printf("Please run with exactly %d processes.\n", ROWS);
        }
        MPI_Finalize();
        return 1;
    }

    if(rank == 0) {
        printf("Enter 4x4 matrix elements:\n");
        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COLS; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
    }

    // Scatter matrix rows to each process
    MPI_Scatter(matrix, COLS, MPI_INT, local_row, COLS, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Op vector_add;
    MPI_Op_create(&vector_add_op, 1, &vector_add);

    // Perform scan (inclusive prefix sum)
    MPI_Scan(local_row, prefix_row, COLS, MPI_INT, vector_add, MPI_COMM_WORLD);

    // Gather all prefix rows back to root
    int result[ROWS][COLS];
    MPI_Gather(prefix_row, COLS, MPI_INT, result, COLS, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("Output matrix:\n");
        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COLS; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Op_free(&vector_add);
    MPI_Finalize();
    return 0;
}
