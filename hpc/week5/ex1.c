#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <ctype.h>

void toggleCase(char *str){
    for(int i=0; str[i]!='\0'; i++){
        if(islower(str[i])){
            str[i] = toupper(str[i]);
        } else if(isupper(str[i])){
            str[i] = tolower(str[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char word[50];

    if(size < 2){
        if(rank == 0){
            printf("The program requires atleast 2 processes\n");
        }
        MPI_Finalize();
        return 0;
    }

    if(rank == 0){
        strcpy(word, "HeLLo");
        printf("Process %d sending: %s\n", rank, word);
        MPI_Ssend(word, strlen(word)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(word, 50, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received word: %s\n", word);
    } else if(rank == 1){
        MPI_Recv(word, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received word: %s\n", rank, word);
        toggleCase(word);
        printf("Process %d toggled the word.\n", rank);
        MPI_Ssend(word, 50, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}