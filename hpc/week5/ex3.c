#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int *arr = NULL;
    int value;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int buf_size = size * (sizeof(int) + MPI_BSEND_OVERHEAD);
    void *buffer = malloc(buf_size);
    MPI_Buffer_attach(buffer, buf_size);

    if (rank == 0) {
        arr = (int *)malloc(size * sizeof(int));

        printf("Enter %d elements:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }

        for (int i = 0; i < size; i++) {
            MPI_Bsend(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        free(arr);

    } else {
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (rank % 2 == 0) {
            printf("Process %d (even): %d^2 = %d\n", rank, value, value * value);
        } else {
            printf("Process %d (odd): %d^3 = %d\n", rank, value, value * value * value);
        }
    }

    MPI_Buffer_detach(&buffer, &buf_size);
    free(buffer);

    MPI_Finalize();
    return 0;
}
