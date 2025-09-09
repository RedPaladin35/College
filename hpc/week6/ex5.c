#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    int data = 0;
    int invalid_root = -1;  // Invalid root rank

    int err = MPI_Bcast(&data, 1, MPI_INT, invalid_root, MPI_COMM_WORLD);
    if (err != MPI_SUCCESS) {
        char error_string[MPI_MAX_ERROR_STRING];
        int length_of_error_string;

        MPI_Error_string(err, error_string, &length_of_error_string);
        if(rank == 0) {
            printf("MPI_Bcast failed with error: %s\n", error_string);
        }
    } else {
        if(rank == 0) {
            printf("MPI_Bcast succeeded.\n");
        }
    }

    MPI_Errhandler new_handler;
    MPI_Comm_create_errhandler(MPI_ERRORS_RETURN, &new_handler);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD, new_handler);

    int invalid_dest = -5;
    err = MPI_Send(&data, 1, MPI_INT, invalid_dest, 0, MPI_COMM_WORLD);

    if (err != MPI_SUCCESS) {
        char error_string[MPI_MAX_ERROR_STRING];
        int length_of_error_string;
        MPI_Error_string(err, error_string, &length_of_error_string);
        if(rank == 0) {
            printf("MPI_Send failed with error: %s\n", error_string);
        }
    }

    MPI_Errhandler_free(&new_handler);

    MPI_Finalize();
    return 0;
}
