#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char str[50] = "HeLLo";
    char c;
    
    MPI_Bcast(str, 50, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank < strlen(str)){
        c = str[rank];
        if(isupper(c)){
            c = tolower(c);
        } else if(islower(c)){
            c = toupper(c);
        }

        if(rank!=0){
            MPI_Send(&c, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        } else {
            str[rank] = c;
        }
    }

    if(rank == 0){
        for(int i=1; i<size; i++){
            if(i < strlen(str)){
                MPI_Recv(&c, 1, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                str[i] = c;
            }
        }
        printf("Toggled string: %s\n", str);
    }
    
    MPI_Finalize();
    return 0;
}