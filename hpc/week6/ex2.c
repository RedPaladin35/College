#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int length = 6;
    const int chunk_size = length / size; // = 2
    char S1[length + 1];
    char S2[length + 1];

    if(rank == 0) {
        printf("Enter string S1 (length 6): ");
        fflush(stdout);
        scanf("%6s", S1);

        printf("Enter string S2 (length 6): ");
        fflush(stdout);
        scanf("%6s", S2);
    }

    MPI_Bcast(S1, length, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(S2, length, MPI_CHAR, 0, MPI_COMM_WORLD);

    char sub_S1[chunk_size + 1];
    char sub_S2[chunk_size + 1];

    MPI_Scatter(S1, chunk_size, MPI_CHAR, sub_S1, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(S2, chunk_size, MPI_CHAR, sub_S2, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    sub_S1[chunk_size] = '\0';
    sub_S2[chunk_size] = '\0';

    char sub_result[2 * chunk_size + 1];
    for(int i = 0; i < chunk_size; i++) {
        sub_result[2*i] = sub_S1[i];
        sub_result[2*i + 1] = sub_S2[i];
    }
    sub_result[2 * chunk_size] = '\0';

    char result[2 * length + 1]; 
    MPI_Gather(sub_result, 2 * chunk_size, MPI_CHAR, result, 2 * chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        result[2 * length] = '\0';
        printf("Resultant String: %s\n", result);
    }

    MPI_Finalize();
    return 0;
}
